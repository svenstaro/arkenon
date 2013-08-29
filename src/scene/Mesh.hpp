#ifndef _SCENE_MESH_HPP
#define _SCENE_MESH_HPP

#include "render/VertexBuffer.hpp"
#include "render/Vertex.hpp"
#include "render/ShaderProgram.hpp"
#include "render/Texture.hpp"
#include "render/Renderable.hpp"

#include "scene/Node.hpp"
#include "scene/Camera.hpp"

#include <memory>

#include <assimp/mesh.h>

class Mesh : public RenderableNode {
public:
    Mesh(const std::string& name);

    void load(const aiMesh* mesh);

    void clear();
    void addTriangle(Vertex a, Vertex b, Vertex c);
    void addQuad(Vertex a, Vertex b, Vertex c, Vertex d);
    void addFace(std::vector<Vertex> vertices);
    void commit();

    void setDiffuseTexture(std::shared_ptr<Texture> texture);
    std::shared_ptr<Texture> getDiffuseTexture();

    void draw();

private:
    VertexBuffer mVertexBuffer;
    std::shared_ptr<Texture> mDiffuseTexture;

};

#endif
