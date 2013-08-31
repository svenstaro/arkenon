#include "Mesh.hpp"

Mesh::Mesh(const std::string& name)
    : RenderableNode(name)
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
            // Get position and normal
            position = mesh->mVertices[face.mIndices[j]];
            normal = mesh->mNormals[face.mIndices[j]];

            // Get UV coordinates, if present
            if(mesh->GetNumUVChannels() > 0)
                uv = mesh->mTextureCoords[0][face.mIndices[j]];

            // Get color value, if present
            if(mesh->GetNumColorChannels() > 0)
                color = mesh->mColors[face.mIndices[j]];
            else
                color = new aiColor4D(1, 1, 1, 1);

            vertices.push_back(Vertex(position.x, position.y, position.z, uv.x, uv.y, color->r, color->g, color->b, color->a, normal.x, normal.y, normal.z));
        }

        addFace(vertices);
    }
}

void Mesh::clear()
{
    mVertexBuffer.clear();
}

void Mesh::addTriangle(Vertex a, Vertex b, Vertex c)
{
    mVertexBuffer.addTriangle(a, b, c);
}

void Mesh::addQuad(Vertex a, Vertex b, Vertex c, Vertex d)
{
    mVertexBuffer.addQuad(a, b, c, d);
}

void Mesh::addFace(std::vector<Vertex> vertices)
{
    for(unsigned int i = 2; i <= vertices.size() - 1; ++i)
    {
        addTriangle(vertices[0], vertices[i-1], vertices[i]);
    }
}

void Mesh::commit()
{
    mVertexBuffer.commit();
}

void Mesh::setMaterial(std::shared_ptr<Material> mat)
{
    mMaterial = mat;
}

std::shared_ptr<Material> Mesh::getMaterial()
{
    return mMaterial;
}

void Mesh::draw()
{
    mVertexBuffer.draw();
}
