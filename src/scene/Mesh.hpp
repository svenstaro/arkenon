#ifndef _SCENE_MESH_HPP
#define _SCENE_MESH_HPP

#include "render/VertexBuffer.hpp"
#include "render/Vertex.hpp"
#include "render/ShaderProgram.hpp"

#include "scene/Node.hpp"
#include "scene/Camera.hpp"

#include <memory>

#include <assimp/mesh.h>

class Mesh : public Node {
public:
    Mesh(const std::string& name);

    void load(const aiMesh* mesh);

    void addTriangle(Vertex a, Vertex b, Vertex c);
    void addQuad(Vertex a, Vertex b, Vertex c, Vertex d);
    void addFace(std::vector<Vertex> vertices);
    void commit();

    void render(Camera* camera, ShaderProgram* shader);

    static Mesh createCube();
    static Mesh createSphere(int rings, int segments);

private:
    VertexBuffer mVertexBuffer;

};

#endif
