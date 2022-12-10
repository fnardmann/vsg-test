#include <vsg/all.h>

#include <iostream>
#include <vector>

struct Point3D 
{
    Point3D(double x_, double y_, double z_)
        : x(x_), y(y_), z(z_) {};

    double x;
    double y;
    double z;
};

int main(int argc, char** argv)
{
    std::vector<Point3D> points {
        Point3D(0.0, 0.0, 0.0),
        Point3D(1.0, 0.0, 0.0),
        Point3D(2.0, 0.0, 0.0),
        Point3D(3.0, 0.0, 0.0),
        Point3D(4.0, 0.0, 1.0)
    };

    vsg::Geometry* geometry = new vsg::Geometry;

    vsg::ref_ptr<vsg::vec3Array> vertices(new vsg::vec3Array(points.size()));

    for (size_t i = 0; i < points.size(); i++)
    {
        vertices->at(i) = vsg::vec3(points[i].x, points[i].y, points[i].z);
    }

    geometry->assignArrays(vsg::DataList{ vertices });

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

    auto scene = vsg::Node::create();
    scene->setObject("hello", geometry);

    // compute the bounds of the scene graph to help position camera
    vsg::ComputeBounds computeBounds;
    scene->accept(computeBounds);
    vsg::dvec3 centre = (computeBounds.bounds.min + computeBounds.bounds.max) * 0.5;
    double radius = vsg::length(computeBounds.bounds.max - computeBounds.bounds.min) * 0.6;
    double nearFarRatio = 0.001;

    // set up the camera
    auto lookAt = vsg::LookAt::create(centre + vsg::dvec3(0.0, -radius * 3.5, 0.0), centre, vsg::dvec3(0.0, 0.0, 1.0));

    vsg::ref_ptr<vsg::ProjectionMatrix> perspective;
    vsg::ref_ptr<vsg::EllipsoidModel> ellipsoidModel(scene->getObject<vsg::EllipsoidModel>("EllipsoidModel"));
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
    auto commandGraph = vsg::createCommandGraphForView(window, camera, scene);
    viewer->assignRecordAndSubmitTaskAndPresentation({commandGraph});

    // compile all Vulkan objects and transfer image, vertex and primitive data to GPU
    viewer->compile();

    // rendering main loop
    while (viewer->advanceToNextFrame())
    {
        // pass any events into EventHandlers assigned to the Viewer
        viewer->handleEvents();

        viewer->update();

        viewer->recordAndSubmit();

        viewer->present();
    }

    // clean up done automatically thanks to ref_ptr<>
    return 0;
}
