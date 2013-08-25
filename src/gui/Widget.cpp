#include "Widget.hpp"

#include <iostream>

Widget::Widget()
    : Node("widget")
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
