#include <vsg/all.h>

#include "Viewer.h"
#include "Scene.h"

#include <iostream>
#include <exception>

vsg::ref_ptr<vsg::Node> load_file(const std::string& path)
{
    // load the scene graph
    auto scenegraph = vsg::read_cast<vsg::Node>(path, vsg::Options::create());
    if (!scenegraph)
    {
        throw std::runtime_error("Could not load vsg scene: " + path);
    }
    return scenegraph;
}

int main()
{
    auto scenegraph = load_file("../teapot.vsgt");

    auto viewer = Viewer(scenegraph);

    // rendering main loop
    Scene::run(viewer);

    return 1;
}