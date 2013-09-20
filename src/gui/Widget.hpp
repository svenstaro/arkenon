#ifndef _GUI_WIDGET_HPP
#define _GUI_WIDGET_HPP

#include <glm/glm.hpp>

#include <memory>
#include <vector>

#include "scene/Node.hpp"

#include "gui/WidgetSkin.hpp"

class Widget : public Node {
public:
    Widget(const std::string& name);
    virtual ~Widget() = 0;

    void setSize(const glm::vec2& size);
    const glm::vec2& getSize() const;

    void setSkin(std::shared_ptr<WidgetSkin> skin);
    std::shared_ptr<WidgetSkin> getSkin();

    bool isPointInside(const glm::vec2& pos);

    virtual bool isFocusable() const;

    void onEvent(const Event* event);

    WidgetSkin::State getState() const;
    bool isFocused() const;
    bool isPressed() const;
    bool isHover() const;

protected:
    virtual void onClick();
    virtual void onFocus();
    virtual void onBlur();

    glm::vec2 mSize;
    std::shared_ptr<WidgetSkin> mSkin;
    WidgetSkin::State mState;
    bool mFocused;
    bool mPressed;
    bool mHover;
    // TODO: disabled

};

#endif
