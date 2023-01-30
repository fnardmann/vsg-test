#include "Scene.h"

void Scene::run(vsg::ref_ptr<vsg::Viewer> viewer)
{
    while (viewer->advanceToNextFrame())
    {
        // pass any events into EventHandlers assigned to the Viewer
        viewer->handleEvents();
        viewer->update();
        viewer->recordAndSubmit();
        viewer->present();
    }
};