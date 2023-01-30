#include "Viewer.h"

Viewer::Viewer(NodePtr scenegraph)
    : viewer(vsg::Viewer::create())
{
    auto window = create_window();
    auto camera = create_camera(scenegraph, window);
    viewer->addWindow(window);

    add_event_handlers(scenegraph, camera);

    // add the CommandGraph to render the scene
    auto commandGraph = vsg::createCommandGraphForView(window, camera, scenegraph);
    viewer->assignRecordAndSubmitTaskAndPresentation({commandGraph});

    // compile all Vulkan objects and transfer image, vertex and primitive data to GPU
    viewer->compile();
}

vsg::ref_ptr<vsg::Window> Viewer::create_window()
{
    auto windowTraits = vsg::WindowTraits::create();
    windowTraits->windowTitle = "Hello World";
    auto window = vsg::Window::create(windowTraits);
    if (!window)
    {
        throw std::runtime_error("Could not create window.");
    }
    return window;
}

vsg::ref_ptr<vsg::Camera> Viewer::create_camera(NodePtr scenegraph, WindowPtr window)
{
    // compute the bounds of the scene graph to help position camera
    vsg::ComputeBounds computeBounds;
    scenegraph->accept(computeBounds);
    vsg::dvec3 centre = (computeBounds.bounds.min + computeBounds.bounds.max) * 0.5;
    double radius = vsg::length(computeBounds.bounds.max - computeBounds.bounds.min) * 0.6;
    double nearFarRatio = 0.001;

    // set up the camera
    auto lookAt = vsg::LookAt::create(centre + vsg::dvec3(0.0, -radius * 3.5, 0.0), centre, vsg::dvec3(0.0, 0.0, 1.0));

    vsg::ref_ptr<vsg::ProjectionMatrix> perspective;
    vsg::ref_ptr<vsg::EllipsoidModel> ellipsoidModel(scenegraph->getObject<vsg::EllipsoidModel>("EllipsoidModel"));
    if (ellipsoidModel)
    {
        double horizonMountainHeight = 0.0;
        perspective = vsg::EllipsoidPerspective::create(lookAt, ellipsoidModel, 30.0, static_cast<double>(window->extent2D().width) / static_cast<double>(window->extent2D().height), nearFarRatio, horizonMountainHeight);
    }
    else
    {
        perspective = vsg::Perspective::create(30.0, static_cast<double>(window->extent2D().width) / static_cast<double>(window->extent2D().height), nearFarRatio * radius, radius * 4.5);
    }

    return vsg::Camera::create(perspective, lookAt, vsg::ViewportState::create(window->extent2D()));
}

void Viewer::add_event_handlers(NodePtr scenegraph, CamPtr camera)
{
    // add close handler to respond the close window button and pressing escape
    viewer->addEventHandler(vsg::CloseHandler::create(viewer));

    // add trackball to control the Camera
    vsg::ref_ptr<vsg::EllipsoidModel> ellipsoidModel(scenegraph->getObject<vsg::EllipsoidModel>("EllipsoidModel"));
    viewer->addEventHandler(vsg::Trackball::create(camera, ellipsoidModel));
}