#include <vsg/all.h>

#include "Scene.h"

#include <iostream>
#include <exception>

vsg::ref_ptr<vsg::Node> load_file(const std::string& path)
{
    // load the scene graph
    auto vsg_scene = vsg::read_cast<vsg::Node>(path, vsg::Options::create());
    if (!vsg_scene)
    {
        throw std::runtime_error("Could not load vsg scene: " + path);
    }
    return vsg_scene;
}

int main()
{
    auto vsg_scene = load_file("../teapot.vsgt");

    // create the viewer and assign window(s) to it
    auto windowTraits = vsg::WindowTraits::create();
    windowTraits->windowTitle = "Hello World";
    auto viewer = vsg::Viewer::create();
    auto window = vsg::Window::create(windowTraits);
    if (!window)
    {
        std::cout << "Could not create windows." << std::endl;
        return 1;
    }

    viewer->addWindow(window);

    // compute the bounds of the scene graph to help position camera
    vsg::ComputeBounds computeBounds;
    vsg_scene->accept(computeBounds);
    vsg::dvec3 centre = (computeBounds.bounds.min + computeBounds.bounds.max) * 0.5;
    double radius = vsg::length(computeBounds.bounds.max - computeBounds.bounds.min) * 0.6;
    double nearFarRatio = 0.001;

    // set up the camera
    auto lookAt = vsg::LookAt::create(centre + vsg::dvec3(0.0, -radius * 3.5, 0.0), centre, vsg::dvec3(0.0, 0.0, 1.0));

    vsg::ref_ptr<vsg::ProjectionMatrix> perspective;
    vsg::ref_ptr<vsg::EllipsoidModel> ellipsoidModel(vsg_scene->getObject<vsg::EllipsoidModel>("EllipsoidModel"));
    if (ellipsoidModel)
    {
        double horizonMountainHeight = 0.0;
        perspective = vsg::EllipsoidPerspective::create(lookAt, ellipsoidModel, 30.0, static_cast<double>(window->extent2D().width) / static_cast<double>(window->extent2D().height), nearFarRatio, horizonMountainHeight);
    }
    else
    {
        perspective = vsg::Perspective::create(30.0, static_cast<double>(window->extent2D().width) / static_cast<double>(window->extent2D().height), nearFarRatio * radius, radius * 4.5);
    }

    auto camera = vsg::Camera::create(perspective, lookAt, vsg::ViewportState::create(window->extent2D()));

    // add close handler to respond the close window button and pressing escape
    viewer->addEventHandler(vsg::CloseHandler::create(viewer));

    // add trackball to control the Camera
    viewer->addEventHandler(vsg::Trackball::create(camera, ellipsoidModel));

    // add the CommandGraph to render the scene
    auto commandGraph = vsg::createCommandGraphForView(window, camera, vsg_scene);
    viewer->assignRecordAndSubmitTaskAndPresentation({commandGraph});

    // compile all Vulkan objects and transfer image, vertex and primitive data to GPU
    viewer->compile();

    // rendering main loop
    Scene::run(viewer);

    // clean up done automatically thanks to ref_ptr<>
    return 0;
}