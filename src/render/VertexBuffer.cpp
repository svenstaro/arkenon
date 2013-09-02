#include "VertexBuffer.hpp"
#include "util/check.hpp"

#include <iostream>

VertexBuffer::VertexBuffer()
{
    glGenVertexArrays(1, &mHandle);
    glGenBuffers(1, &mHandleVertexBuffer);
    glGenBuffers(1, &mHandleUVBuffer);
    glGenBuffers(1, &mHandleColorBuffer);
    glGenBuffers(1, &mHandleNormalBuffer);
    glGenBuffers(1, &mHandleTangentBuffer);
    glGenBuffers(1, &mHandleBitangentBuffer);
    glGenBuffers(1, &mHandleIndexBuffer);
    GL_CHECK();
}

void VertexBuffer::clear()
{
    mVertices.clear();
    mUVs.clear();
    mColors.clear();
    mNormals.clear();
    mTangents.clear();
    mBitangents.clear();
    mIndices.clear();
}

unsigned int VertexBuffer::addVertex(const Vertex& vertex, bool force_new)
{
    if(!force_new)
    {
        // try to find an existing vertex
        for(unsigned int i = 0; i < mVertices.size(); ++i)
        {
            if(mVertices[i] == vertex.position &&
                    mUVs[i] == vertex.uv &&
                    mColors[i] == vertex.color &&
                    mNormals[i] == vertex.normal &&
                    mTangents[i] == vertex.tangent &&
                    mBitangents[i] == vertex.bitangent)
            {
                // we found an existing vertex like this one, just use that
                return i;
            }
        }
    }

    mVertices.push_back(vertex.position);
    mUVs.push_back(vertex.uv);
    mColors.push_back(vertex.color);
    mNormals.push_back(vertex.normal);
    mTangents.push_back(vertex.tangent);
    mBitangents.push_back(vertex.bitangent);
    return mVertices.size() - 1;
}

void VertexBuffer::makeTriangle(unsigned int ai, unsigned int bi, unsigned int ci, bool calculateTangents)
{
    // calculate tangents if requested, normals are available and tangents are not supplied
    // TODO: ... && a.hasNormal() && b.hasNormal() && c.hasNormal() && !a.hasTangents() && !b.hasTangents() && !c.hasTangents()
    if(calculateTangents &&
            (mNormals[ai].x != 0 || mNormals[ai].y != 0 || mNormals[ai].z != 0) &&
            (mNormals[bi].x != 0 || mNormals[bi].y != 0 || mNormals[bi].z != 0) &&
            (mNormals[ci].x != 0 || mNormals[ci].y != 0 || mNormals[ci].z != 0))
    {
        // Edges of the triangle
        glm::vec3 delta1 = mVertices[bi] - mVertices[ai];
        glm::vec3 delta2 = mVertices[ci] - mVertices[ai];

        // UV delta
        glm::vec2 deltaUV1 = mUVs[bi] - mUVs[ai];
        glm::vec2 deltaUV2 = mUVs[ci] - mUVs[ai];

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec3 tangent = (delta1 * deltaUV2.y   - delta2 * deltaUV1.y)*r;
        glm::vec3 bitangent = (delta2 * deltaUV1.x   - delta1 * deltaUV2.x)*r;

        mTangents[ai] = mTangents[bi] = mTangents[ci] = tangent;
        mBitangents[ai] = mBitangents[bi] = mBitangents[ci] = bitangent;
    }

    mIndices.push_back(ai);
    mIndices.push_back(bi);
    mIndices.push_back(ci);
}

void VertexBuffer::makeQuad(unsigned int ai, unsigned int bi, unsigned int ci, unsigned int di, bool calculateTangents)
{
    makeTriangle(ai, bi, ci, calculateTangents);
    makeTriangle(ai, ci, di, calculateTangents);
}

void VertexBuffer::addTriangle(Vertex a, Vertex b, Vertex c, bool calculateTangents)
{
    makeTriangle(addVertex(a), addVertex(b), addVertex(c), calculateTangents);
}

void VertexBuffer::addQuad(Vertex a, Vertex b, Vertex c, Vertex d, bool calculateTangents)
{
    makeQuad(addVertex(a), addVertex(b), addVertex(c), addVertex(d), calculateTangents);
}


void VertexBuffer::commit()
{
    const static unsigned int vertexAttribute = 0;
    const static unsigned int uvAttribute = 1;
    const static unsigned int colorAttribute = 2;
    const static unsigned int normalAttribute = 3;
    const static unsigned int tangentAttribute = 4;
    const static unsigned int bitangentAttribute = 5;

    glBindVertexArray(mHandle);

    //Vertices
    glBindBuffer(GL_ARRAY_BUFFER, mHandleVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mVertices.size() , &mVertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(vertexAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(vertexAttribute);
    GL_CHECK();

    //Texture Coordinates
    glBindBuffer(GL_ARRAY_BUFFER, mHandleUVBuffer);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(glm::vec2) * mUVs.size(), &mUVs[0], GL_STATIC_DRAW);
    glVertexAttribPointer(uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
    glEnableVertexAttribArray(uvAttribute);
    GL_CHECK();

    //Colors
    glBindBuffer(GL_ARRAY_BUFFER, mHandleColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, mColors.size() * sizeof(glm::vec4), &mColors[0], GL_STATIC_DRAW);
    glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);
    glEnableVertexAttribArray(colorAttribute);
    GL_CHECK();

    //Normals
    glBindBuffer(GL_ARRAY_BUFFER, mHandleNormalBuffer);
    glBufferData(GL_ARRAY_BUFFER, mNormals.size() * sizeof(glm::vec3), &mNormals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(normalAttribute);
    GL_CHECK();

    //Tangents
    glBindBuffer(GL_ARRAY_BUFFER, mHandleTangentBuffer);
    glBufferData(GL_ARRAY_BUFFER, mTangents.size() * sizeof(glm::vec3), &mTangents[0], GL_STATIC_DRAW);
    glVertexAttribPointer(tangentAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(tangentAttribute);
    GL_CHECK();

    //Bitangent
    glBindBuffer(GL_ARRAY_BUFFER, mHandleBitangentBuffer);
    glBufferData(GL_ARRAY_BUFFER, mBitangents.size() * sizeof(glm::vec3), &mBitangents[0], GL_STATIC_DRAW);
    glVertexAttribPointer(bitangentAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(bitangentAttribute);
    GL_CHECK();

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mHandleIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mIndices.size(), &mIndices[0], GL_STATIC_DRAW);
    GL_CHECK();
}

void VertexBuffer::bind()
{
    std::cout << "MEH" << std::endl;
}

void VertexBuffer::draw()
{
    glBindVertexArray(mHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mHandleIndexBuffer);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, (void*)0);
    GL_CHECK();
}
