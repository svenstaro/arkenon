#include "Widget.hpp"

#include <iostream>

Widget::Widget(const std::string& name)
    : Node(name),
      mState(WidgetSkin::Normal)
{
}

Widget::~Widget()
{}

void Widget::setSize(const glm::vec2& size)
{
    mSize = size;
    //scale = glm::vec3(size.x, size.y, 1.f);
}

const glm::vec2& Widget::getSize() const
{
    return mSize;
    //return glm::vec2(scale.x, scale.y);
}

void Widget::setSkin(std::shared_ptr<WidgetSkin> skin)
{
    mSkin = skin;
}

std::shared_ptr<WidgetSkin> Widget::getSkin()
{
    return mSkin;
}

bool Widget::isPointInside(const glm::vec2& pos)
{
    //TODO: camera projection
    glm::vec4 lm = glm::inverse(getAbsoluteTransformationMatrix()) * glm::vec4(pos.x, pos.y, 0.f, 1.f);
    return lm.x >= 0 && lm.y >= 0 && lm.x <= mSize.x && lm.y <= mSize.y;
}

bool Widget::isFocusable() const
{
    return false;
}

void Widget::onEvent(const Event* event)
{
    switch(event->type)
    {
        case Event::MouseMove:
            mHover = isPointInside(((MouseMoveEvent*)event)->position);
            break;
        case Event::MousePress:
            if(isPointInside(((MouseMoveEvent*)event)->position)) {
                mPressed = true;
                mFocused = true;
                onFocus();
            } else {
                mFocused = false;
                onBlur();
            }
            break;
        case Event::MouseRelease:
            mPressed = false;
            if(isPointInside(((MouseMoveEvent*)event)->position)) {
                onClick();
            }
            break;
        default:
            return; // do not even change the state
    }

    // set skin depending on actual state
    // TODO: disabled
    mState = mPressed           ? WidgetSkin::Active :
            (mHover || mFocused ? WidgetSkin::Focus :
                                  WidgetSkin::Normal);
}

WidgetSkin::State Widget::getState() const
{
    return mState;
}

bool Widget::isFocused() const
{
    return mFocused;
}

bool Widget::isPressed() const
{
    return mPressed;
}

bool Widget::isHover() const
{
    return mHover;
}

void Widget::onClick() {}
void Widget::onFocus() {}
void Widget::onBlur() {}
