#ifndef _RENDER_VERTEXBUFFER_HPP
#define _RENDER_VERTEXBUFFER_HPP

#include <GL/glew.h>
#include <vector>

#include "render/Vertex.hpp"

class VertexBuffer {
public:
    VertexBuffer();
    void addVertex(const Vertex& vertex);
    void commit();
    void bind();
    void draw();

    GLuint getHandle() const;

private:
    std::vector<Vertex> mBuffer;
    GLuint mHandle;

};

#endif
