#ifndef _RENDER_RENDERTARGET_HPP
#define _RENDER_RENDERTARGET_HPP

#include <glm/glm.hpp>

class RenderTarget {
public:
    RenderTarget(glm::vec2 size);
    virtual ~RenderTarget() = 0;
    virtual void setActive() = 0;

    const glm::vec2& getSize() const;

protected:
    glm::vec2 mSize;

};

#endif
