#include "Rect.hpp"

Rect::Rect(float x, float y, float w, float h)
    : Rect(glm::vec2(x, y), glm::vec2(w, h))
{}

Rect::Rect(const glm::vec2& _position, const glm::vec2& _size)
{
    position = _position;
    size = _size;
}
