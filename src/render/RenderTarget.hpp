#ifndef _RENDER_RENDERTARGET_HPP
#define _RENDER_RENDERTARGET_HPP

#include <glm/glm.hpp>

class RenderTarget {
public:
    /**
     * Initializes a RenderTarget.
     * @param size The size, in pixels, for this target.
     */
    RenderTarget(glm::vec2 size = glm::vec2(0, 0));

    virtual ~RenderTarget() = 0;

    /**
     * Sets this RenderTarget as the currently active one. All following
     * OpenGL rendering operations will be performed on this target.
     */
    virtual void bind() = 0;

    /**
     * Returs the size of the RenderTarget.
     * @return The size in pixels.
     */
    virtual glm::vec2 getSize() const;

    /**
     * Changes the size of the RenderTarget.
     * @param size The new size, in pixels.
     */
    virtual void setSize(const glm::vec2& size);

private:
    glm::vec2 mSize;

};

#endif
