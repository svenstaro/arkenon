#include "Renderer.hpp"

void Renderer::prepare()
{
    // nothing to do
}


void Renderer::registerMesh(Mesh* mesh)
{
    mMeshes.push_back(mesh);
}


void Renderer::setCamera(Camera* camera)
{
    mCamera = camera;
}


void Renderer::cleanup()
{
    mMeshes.clear();
}
