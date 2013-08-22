#include "Vertex.hpp"

Vertex::Vertex(float x, float y, float z,
               float u, float v,
               float r, float g, float b, float a,
               float nx, float ny, float nz)
    : Vertex(glm::vec3(x, y, z), glm::vec2(u, v), glm::vec4(r, g, b, a), glm::vec3(nx, ny, nz))
{}

Vertex::Vertex(glm::vec3 _position,
               glm::vec2 _uv = glm::vec2(0, 0),
               glm::vec4 _color = glm::vec4(1.0, 1.0, 1.0, 1.0),
               glm::vec3 _normal = glm::vec3(0, 0, 0))
    : position(_position),
      uv(_uv),
      color(_color),
      normal(_normal)
{}
