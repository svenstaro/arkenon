#ifndef _RENDER_RENDERER_HPP
#define _RENDER_RENDERER_HPP

#include "scene/Mesh.hpp"
#include "scene/Camera.hpp"

#include <vector>

class Renderer {
public:
    virtual void prepare();
    void registerMesh(Mesh* mesh);
    void setCamera(Camera* camera);
    virtual void render() = 0;
    virtual void cleanup();

protected:
    std::vector<Mesh*> mMeshes;
    Camera* mCamera;

};

#endif
