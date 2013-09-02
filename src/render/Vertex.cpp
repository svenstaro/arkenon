#include "Vertex.hpp"

Vertex::Vertex(float x, float y, float z,
               float u, float v,
               float r, float g, float b, float a,
               float nx, float ny, float nz,
               float tx, float ty, float tz,
               float btx, float bty, float btz)
    : Vertex(glm::vec3(x, y, z), glm::vec2(u, v), glm::vec4(r, g, b, a), glm::vec3(nx, ny, nz), glm::vec3(tx, ty, tz), glm::vec3(btx, bty, btz))
{}

Vertex::Vertex(glm::vec3 _position,
               glm::vec2 _uv,
               glm::vec4 _color,
               glm::vec3 _normal,
               glm::vec3 _tangent,
               glm::vec3 _bitangent)
    : position(_position),
      uv(_uv),
      color(_color),
      normal(_normal),
      tangent(_tangent),
      bitangent(_bitangent)
{}

bool Vertex::hasNormal()
{
    return normal.x != 0 || normal.y != 0 || normal.z != 0;
}

bool Vertex::hasTangents()
{
    bool hasTangent = tangent.x != 0 || tangent.y != 0 || tangent.z != 0;
    bool hasBitangent = bitangent.x != 0 || bitangent.y != 0 || bitangent.z != 0;
    return hasTangent && hasBitangent;
}
