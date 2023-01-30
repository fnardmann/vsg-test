#ifndef VIEWER_H_INCLUDED
#define VIEWER_H_INCLUDED

#include <vsg/all.h>

class Viewer
{
    using CamPtr = vsg::ref_ptr<vsg::Camera>;
    using NodePtr = vsg::ref_ptr<vsg::Node>;
    using WindowPtr = vsg::ref_ptr<vsg::Window>;

public:

    Viewer(vsg::ref_ptr<vsg::Node> scenegraph);

    vsg::ref_ptr<vsg::Viewer> get_viewer() const { return viewer; };

private:

    vsg::ref_ptr<vsg::Window> create_window();

    vsg::ref_ptr<vsg::Camera> create_camera(NodePtr scenegraph, WindowPtr window);

    void add_event_handlers(NodePtr scenegraph, CamPtr camera);

    vsg::ref_ptr<vsg::Viewer> viewer;
};

#endif