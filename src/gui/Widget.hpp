#ifndef _GUI_WIDGET_HPP
#define _GUI_WIDGET_HPP

#include <glm/glm.hpp>

#include <memory>
#include <vector>

#include "scene/Node.hpp"
#include "render/Renderable.hpp"

class Widget : public RenderableNode {
public:
    Widget();
    virtual ~Widget() = 0;

    void setSize(const glm::vec2& size);
    const glm::vec2& getSize() const;

protected:
    glm::vec2 mSize;

};

#endif
