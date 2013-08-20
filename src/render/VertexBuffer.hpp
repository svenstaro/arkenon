#ifndef _RENDER_VERTEXBUFFER_HPP
#define _RENDER_VERTEXBUFFER_HPP

#include <GL/glew.h>
#include <vector>

class VertexBuffer {
public:
    VertexBuffer();
    void addVertex(float x, float y, float z);
    void commit();
    void bind();
    void draw();

    GLuint getHandle() const;

private:
    std::vector<float> mBuffer;
    GLuint mHandle;

};

#endif
