#include "Shape3D.hpp"

Shape3D::Shape3D(const std::string& name)
    : RenderableNode(name)
{}

void Shape3D::makeUvSphere(unsigned int rings, unsigned int sectors)
{
    float const R = 1.0/(float)(rings-1);
    float const S = 1.0/(float)(sectors-1);
    Vertex vertices[rings * sectors];

    for(unsigned int r = 0; r < rings; r++) {
        for(unsigned int s = 0; s < sectors; s++) {
            float const y = sin(-M_PI_2 + M_PI * r * R);
            float const x = cos(2*M_PI * s * S) * sin(M_PI * r * R);
            float const z = sin(2*M_PI * s * S) * sin(M_PI * r * R);

            vertices[r*sectors+s] = Vertex(
                glm::vec3(x, y, z),
                //glm::vec2(s * S, r * R),
                glm::vec2(0, 0),
                glm::vec4(1.f, 1.f, 1.f, 1.f),
                glm::vec3(x, y, z));
        }
    }

    mVertexBuffer.clear();
    for(int r = 0; r < rings-1; r++) { // do not draw the top ring, it contains only the top vertex anyway (thus -1)
        for(int s = 0; s < sectors-1; s++) {
            mVertexBuffer.addQuad(
                vertices[r * sectors + s],
                vertices[r * sectors + (s + 1)],
                vertices[(r + 1) * sectors + (s + 1)],
                vertices[(r + 1) * sectors + s]);
        }
    }
    mVertexBuffer.commit();
}

void Shape3D::draw()
{
    mVertexBuffer.draw();
}
