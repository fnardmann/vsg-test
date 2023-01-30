#include "Scene.h"

void Scene::run(const Viewer& viewer)
{
    auto vsg_viewer = viewer.get_viewer();
    while (vsg_viewer->advanceToNextFrame())
    {
        // pass any events into EventHandlers assigned to the Viewer
        vsg_viewer->handleEvents();
        vsg_viewer->update();
        vsg_viewer->recordAndSubmit();
        vsg_viewer->present();
    }
};