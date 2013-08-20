#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &mHandle);
}

void VertexBuffer::addVertex(float x, float y, float z)
{
    mBuffer.push_back(x);
    mBuffer.push_back(y);
    mBuffer.push_back(z);
}

void VertexBuffer::commit()
{
    bind();

    /* Upload vertex data to the video device */
    glBufferData(GL_ARRAY_BUFFER, mBuffer.size() * 3 * sizeof(float), &mBuffer[0], GL_STATIC_DRAW);

    /* Specify that our coordinate data is going into attribute index 0(shaderAttribute), and contains three floats per vertex */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, mHandle);
}

void VertexBuffer::draw()
{
    bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
