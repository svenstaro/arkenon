#ifndef _SCENE_SHAPE3D_HPP
#define _SCENE_SHAPE3D_HPP

#include <memory>

#include "render/VertexBuffer.hpp"
#include "render/Vertex.hpp"
#include "render/ShaderProgram.hpp"
#include "render/Renderable.hpp"
#include "scene/Node.hpp"
#include "scene/Camera.hpp"

class Shape3D : public RenderableNode {
public:
    Shape3D(const std::string& name);

    void makeUvSphere(unsigned int rings, unsigned int sectors);

    void draw();

private:
    VertexBuffer mVertexBuffer;

};

#endif
