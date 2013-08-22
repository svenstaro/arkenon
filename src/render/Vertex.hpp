#ifndef _RENDER_VERTEX_HPP
#define _RENDER_VERTEX_HPP

#include <glm/glm.hpp>

class Vertex
{
public:
    Vertex(float x, float y, float z,
           float u = 0.f, float v = 0.f,
           float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f,
           float nx = 0.f, float ny = 0.f, float nz = 0.f);
    Vertex(glm::vec3 _position, glm::vec2 _uv, glm::vec4 _color, glm::vec3 _normal);

private:
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec4 color;
    glm::vec3 normal;
};

#endif
