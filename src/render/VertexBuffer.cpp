#include "VertexBuffer.hpp"
#include "util/check.hpp"

#include <iostream>

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &mHandle);
    GL_CHECK();
}

void VertexBuffer::clear()
{
    mBuffer.clear();
}

void VertexBuffer::addVertex(const Vertex& vertex)
{
    mBuffer.push_back(vertex);
}

void VertexBuffer::addTriangle(Vertex a, Vertex b, Vertex c)
{
    addVertex(a);
    addVertex(b);
    addVertex(c);
}

void VertexBuffer::addQuad(Vertex a, Vertex b, Vertex c, Vertex d)
{
    addTriangle(a, b, c);
    addTriangle(a, c, d);
}

void VertexBuffer::commit()
{
    bind();

    glBufferData(GL_ARRAY_BUFFER, mBuffer.size() * sizeof(Vertex), &mBuffer[0], GL_STATIC_DRAW);
    GL_CHECK();

}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, mHandle);
    GL_CHECK();
}

void VertexBuffer::draw()
{
    bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0 * sizeof(float)));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
    GL_CHECK();

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    GL_CHECK();

    glDrawArrays(GL_TRIANGLES, 0, mBuffer.size());
    GL_CHECK();
}
