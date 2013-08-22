#include "Mesh.hpp"

Mesh::Mesh(const std::string& name)
    : Node(name)
{}

void Mesh::load(const aiMesh* mesh)
{
    aiVector3D uv, normal, position;
    aiColor4D* color;

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];

        std::vector<Vertex> vertices;

        for(unsigned int j = 0; j < face.mNumIndices; j++)
        {
            uv = mesh->mTextureCoords[0][face.mIndices[j]];
            normal = mesh->mNormals[face.mIndices[j]];
            position = mesh->mVertices[face.mIndices[j]];
            vertices.push_back(Vertex(position.x, position.y, position.z, uv.x, uv.y, 1.f, 1.f, 1.f, 1.f, normal.x, normal.y, normal.z));
        }

        addFace(vertices);
    }
}

void Mesh::addTriangle(Vertex a, Vertex b, Vertex c)
{
    mVertexBuffer.addVertex(a);
    mVertexBuffer.addVertex(b);
    mVertexBuffer.addVertex(c);
}

void Mesh::addQuad(Vertex a, Vertex b, Vertex c, Vertex d)
{
    addTriangle(a, b, c);
    addTriangle(a, c, d);
}

void Mesh::addFace(std::vector<Vertex> vertices)
{
    for(int i = 2; i <= vertices.size() - 1; ++i)
    {
        addTriangle(vertices[0], vertices[i-1], vertices[i]);
    }
}

void Mesh::commit()
{
    mVertexBuffer.commit();
}

void Mesh::setDiffuseTexture(Texture* texture)
{
    mDiffuseTexture = texture;
}

void Mesh::render(Camera* camera, ShaderProgram* shader)
{
    shader->use();

    glm::mat4 MVP = camera->getViewProjectionMatrix() * getTransformationMatrix();
    shader->send("MVP", MVP);
    shader->send("diffuse_texture", mDiffuseTexture, 0);
    mVertexBuffer.draw();
}

Mesh Mesh::createCube()
{

}

Mesh Mesh::createSphere(int rings, int segments)
{

}
