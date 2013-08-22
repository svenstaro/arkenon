#include "Mesh.hpp"

Mesh::Mesh(const std::string& name, ShaderProgram* shader_program)
    : Node(name)
{
    mShaderProgram = shader_program;
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
    addTriangle(c, d, a);
}

void Mesh::commit()
{
    mVertexBuffer.commit();
}

void Mesh::render(Camera* camera)
{
    mShaderProgram->use();

    glm::mat4 MVP = camera->getViewProjectionMatrix() * getTransformationMatrix();
    mShaderProgram->send("MVP", MVP);

    mVertexBuffer.draw();
}

Mesh Mesh::createCube()
{

}

Mesh Mesh::createSphere(int rings, int segments)
{

}
