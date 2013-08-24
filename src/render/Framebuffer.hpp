#ifndef _RENDER_FRAMEBUFFER_HPP
#define _RENDER_FRAMEBUFFER_HPP

#include <GL/glew.h>

#include "Texture.hpp"

#include "render/RenderTarget.hpp"

class Framebuffer : public RenderTarget {
public:
    Framebuffer(glm::vec2 size);

    /**
     * Binds this Framebuffer for OpenGL operations.
     */
    void bind();

    void setActive();

    /**
     * Returns the texture that contains the rendered result.
     * @return The Framebuffer texture.
     */
    Texture* getTexture();

private:
    GLuint mHandle;
    Texture mTexture;
    GLuint mDepthbuffer;

};

#endif
