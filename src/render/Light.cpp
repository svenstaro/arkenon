#include "Light.hpp"

Light::Light(const std::string& name) 
	: Node(name) {}

void Light::setColor(const glm::vec4& color) {
	mColor = color;
}

void Light::setRadius(float r) {
	mRadius = r;
}

glm::vec4 Light::getColor() {
	return mColor;
}

float Light::getRadius() {
	return mRadius;
}