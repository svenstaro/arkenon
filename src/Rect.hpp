#ifndef _GUI_RECT_HPP
#define _GUI_RECT_HPP

#include <glm/glm.hpp>

class Rect {
public:
    Rect(float x = 0, float y = 0, float w = 1, float h = 1);
    Rect(const glm::vec2& _position, const glm::vec2& _size);

public:
    glm::vec2 position;
    glm::vec2 size;

};

#endif
