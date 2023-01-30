#ifndef VIEWER_H_INCLUDED
#define VIEWER_H_INCLUDED

#include <vsg/all.h>

class Viewer
{
public:

    Viewer(vsg::ref_ptr<vsg::Node> scenegraph);

    vsg::ref_ptr<vsg::Viewer> get_viewer() const { return viewer; };

private:

    vsg::ref_ptr<vsg::Window> create_window();

    vsg::ref_ptr<vsg::Camera> create_camera(
        vsg::ref_ptr<vsg::Node> scenegraph, vsg::ref_ptr<vsg::Window> window);

    vsg::ref_ptr<vsg::Viewer> viewer;
};

#endif