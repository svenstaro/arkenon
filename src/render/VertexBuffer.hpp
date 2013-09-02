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
     * Adds the vertex to the buffers.
     * @param vertex The vertex data.
     * @param force_new If false, the existing vertices are searched for an identical vertex for reuse with the index buffer.
     * @return The new vertex' index.
     */
    unsigned int addVertex(const Vertex& vertex, bool force_new = false);

    /**
     * Creates a triangle from existing data;
     */
    void makeTriangle(unsigned int ai, unsigned int bi, unsigned int ci, bool calculateTangents = true);

    /**
     * Creates a quad from existing data;
     */
    void makeQuad(unsigned int ai, unsigned int bi, unsigned int ci, unsigned int di, bool calculateTangents = true);

    /**
     * Adds a triangle to the buffer.
     */
    void addTriangle(Vertex a, Vertex b, Vertex c, bool calculateTangents = true);

    /**
     * Adds a quad to the buffer.
     */
    void addQuad(Vertex a, Vertex b, Vertex c, Vertex d, bool calculateTangents = true);

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
    std::vector<glm::vec3> mVertices;
    std::vector<glm::vec2> mUVs;
    std::vector<glm::vec4> mColors;
    std::vector<glm::vec3> mNormals;
    std::vector<glm::vec3> mTangents;
    std::vector<glm::vec3> mBitangents; // this is sometimes called "binormal", but it's the same
    std::vector<GLuint> mIndices;

    GLuint mHandle; // array handle
    GLuint mHandleVertexBuffer;
    GLuint mHandleUVBuffer;
    GLuint mHandleColorBuffer;
    GLuint mHandleNormalBuffer;
    GLuint mHandleTangentBuffer;
    GLuint mHandleBitangentBuffer;
    GLuint mHandleIndexBuffer;

};

#endif
