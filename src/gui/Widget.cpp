#include "Widget.hpp"

#include <iostream>

Widget::Widget(const std::string& name)
    : Node(name)
{}

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
