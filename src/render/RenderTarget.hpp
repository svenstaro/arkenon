#ifndef _RENDER_RENDERTARGET_HPP
#define _RENDER_RENDERTARGET_HPP

#include <glm/glm.hpp>

class RenderTarget {
public:
    /**
     * Initializes a RenderTarget.
     * @param size The size, in pixels, for this target.
     */
    RenderTarget(glm::vec2 size);

    virtual ~RenderTarget() = 0;

    /**
     * Sets this RenderTarget as the currently active one. All following
     * OpenGL rendering operations will be performed on this target.
     */
    virtual void setActive() = 0;

    /**
     * Returs the size of the RenderTarget.
     * @return The size in pixels.
     */
    const glm::vec2& getSize() const;

protected:
    glm::vec2 mSize;

};

#endif
