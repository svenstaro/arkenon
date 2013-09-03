#ifndef _RENDER_VERTEX_HPP
#define _RENDER_VERTEX_HPP

#include <glm/glm.hpp>

class Vertex
{
public:
    Vertex(float x = 0.f, float y = 0.f, float z = 0.f,
           float u = 0.f, float v = 0.f,
           float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f,
           float nx = 0.f, float ny = 0.f, float nz = -1.f,
           float tx = 1.f, float ty = 0.f, float tz = 0.f,
           float btx = 0.f, float bty = 1.f, float btz = 0.f);
    Vertex(glm::vec3 _position,
           glm::vec2 _uv = glm::vec2(0, 0),
           glm::vec4 _color = glm::vec4(1, 1, 1, 1),
           glm::vec3 _normal = glm::vec3(0, 0, 0),
           glm::vec3 _tangent = glm::vec3(0, 0 ,0),
           glm::vec3 _bitangent = glm::vec3(0, 0 ,0));

    bool hasNormal();
    bool hasTangents();

    glm::vec3 position;
    glm::vec2 uv;
    glm::vec4 color;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

#endif
