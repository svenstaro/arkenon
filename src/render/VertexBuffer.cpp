#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &mHandle);
}

void VertexBuffer::addVertex(const Vertex& vertex)
{
    mBuffer.push_back(vertex);
}

void VertexBuffer::commit()
{
    bind();

    glBufferData(GL_ARRAY_BUFFER, mBuffer.size() * sizeof(Vertex), &mBuffer[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0 * sizeof(float)));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, mHandle);
}

void VertexBuffer::draw()
{
    bind();
    glDrawArrays(GL_TRIANGLES, 0, mBuffer.size());
}
