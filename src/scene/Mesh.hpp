#ifndef _SCENE_MESH_HPP
#define _SCENE_MESH_HPP

#include "render/VertexBuffer.hpp"
#include "render/Vertex.hpp"
#include "render/ShaderProgram.hpp"

#include "scene/Node.hpp"
#include "scene/Camera.hpp"

#include <memory>

class Mesh : public Node {
public:
    Mesh(const std::string& name, ShaderProgram* shader_program);

    void addTriangle(Vertex a, Vertex b, Vertex c);
    void addQuad(Vertex a, Vertex b, Vertex c, Vertex d);
    void commit();

    void render(Camera* camera);

    static Mesh createCube();
    static Mesh createSphere(int rings, int segments);

private:
    VertexBuffer mVertexBuffer;
    ShaderProgram* mShaderProgram;

};

#endif
