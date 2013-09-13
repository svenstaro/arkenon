#include "Mesh.hpp"

Mesh::Mesh(const std::string& name)
    : RenderableNode(name)
{}

void Mesh::load(const aiMesh* mesh)
{
    aiVector3D uv, normal, pos, tangent, bitangent;
    uv = normal = pos = aiVector3D(0, 0, 0);
    tangent = aiVector3D(1, 0, 0);
    bitangent = aiVector3D(0, 1, 0);

    aiColor4D* color = new aiColor4D(1, 1, 1, 1);

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];

        std::vector<Vertex> vertices;

        for(unsigned int j = 0; j < face.mNumIndices; j++)
        {
            if(mesh->HasPositions())
                pos = mesh->mVertices[face.mIndices[j]];

            if(mesh->HasNormals())
                normal = mesh->mNormals[face.mIndices[j]];

            // These are still buggy
            //if(mesh->HasTangentsAndBitangents())
            //{
            //    tangent = mesh->mTangents[face.mIndices[j]];
            //    bitangent = mesh->mBitangents[face.mIndices[j]];
            //}

            if(mesh->HasTextureCoords(0))
                uv = mesh->mTextureCoords[0][face.mIndices[j]];

            if(mesh->HasVertexColors(0))
                color = mesh->mColors[face.mIndices[j]];

            vertices.push_back(Vertex(
                                   pos.x, pos.y, pos.z,
                                   uv.x, uv.y,
                                   color->r, color->g, color->b, color->a,
                                   normal.x, normal.y, normal.z,
                                   tangent.x, tangent.y, tangent.z,
                                   bitangent.x, bitangent.y, bitangent.z));
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
