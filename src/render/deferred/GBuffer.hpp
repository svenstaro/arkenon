#ifndef _RENDER_DEFERRED_GBUFFER_HPP
#define _RENDER_DEFERRED_GBUFFER_HPP

#include <GL/glew.h>

#include "render/ShaderProgram.hpp"
#include <memory>

class GBuffer {
public:
    GBuffer(glm::vec2 size);

    ~GBuffer();

    /**
     * Binds this Framebuffer for OpenGL operations.
     */
    void bind(BindType type);

    void setReadBuffer(BufferType type);

    void bindTextures(std::shared_ptr<ShaderProgram> shader_program);
private:
    const static unsigned int NUM_TEXTURES = 4;

    glm::vec2 mSize;
    GLuint mHandle;
    GLuint mBuffers[NUM_TEXTURES];
    GLuint mDepthStencilBuffer;
    GLuint mFinalBuffer;
};

#endif
