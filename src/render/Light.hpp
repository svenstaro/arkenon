#ifndef _RENDER_LIGHT_HPP
#define _RENDER_LIGHT_HPP

#include "scene/Node.hpp"

#include <memory>
#include <glm/glm.hpp>

class Light : public Node {
public:
    Light(const std::string& name);

    void setRadius(float r);
    void setColor(const glm::vec4& color);

    float getRadius();
    glm::vec4 getColor();

private:
	glm::vec4 mColor;
	float mRadius;
};

#endif
