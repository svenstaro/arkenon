#ifndef _RENDER_VERTEXBUFFER_HPP
#define _RENDER_VERTEXBUFFER_HPP

#include <GL/glew.h>
#include <vector>

#include "render/Vertex.hpp"

class VertexBuffer {
public:
    /**
     * Initializes a vertex buffer.
     */
    VertexBuffer();

    /**
     * Clears the vertices from the buffer.
     */
    void clear();

    /**
     * Adds a vertex to the buffer.
     * @param vertex The vertex.
     */
    void addVertex(const Vertex& vertex);

    /**
     * Adds a triangle to the buffer.
     */
    void addTriangle(Vertex a, Vertex b, Vertex c);

    /**
     * Adds a quad to the buffer.
     */
    void addQuad(Vertex a, Vertex b, Vertex c, Vertex d);

    /**
     * Sends all vertices to the graphics card memory.
     */
    void commit();

    /**
     * Binds this VertexBuffer for OpenGL operations.
     */
    void bind();

    /**
     * Draws this VertexBuffer.
     */
    void draw();

    /**
     * Returns the OpenGL handle of this VertexBuffer for direct access.
     * @return The OpenGL VBO id.
     */
    GLuint getHandle() const;

private:
    std::vector<Vertex> mBuffer;
    GLuint mHandle;

};

#endif
