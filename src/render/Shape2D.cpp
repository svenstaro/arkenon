#include "Shape2D.hpp"

Shape2D::Shape2D(const std::string& name)
    : Node(name, Default)
{}

void Shape2D::makeRectangle(const glm::vec2& size, const Rect& subrect, const Rect& splitMiddle, const glm::vec2& texture_size)
{
    glm::vec2 tex_size = texture_size;
    if(tex_size.x == 0 && tex_size.y == 0)
    {
        if(mMaterial)
        {
            tex_size = mMaterial->getDiffuseTexture()->getSize();
        }
        else
        {
            std::cerr << "Set a texture or provide a texture_size for makeRectangle()." << std::endl;
            return;
        }
    }

    if(splitMiddle.position.x == 0 && splitMiddle.position.y == 0 && splitMiddle.size.x == 1 && splitMiddle.size.y == 1)
    {
        // Texture: Start/End
        glm::vec2 ts = subrect.position;
        glm::vec2 te = (subrect.position + subrect.size);

        // Vertex: Start/End
        glm::vec2 vs(0, 0);
        glm::vec2 ve = size;

        mVertexBuffer.clear();
        mVertexBuffer.addQuad(
            Vertex(vs.x, vs.y, 0, ts.x, -ts.y, 1, 1, 1, 1, 0, 0, -1),
            Vertex(ve.x, vs.y, 0, te.x, -ts.y, 1, 1, 1, 1, 0, 0, -1),
            Vertex(ve.x, ve.y, 0, te.x, -te.y, 1, 1, 1, 1, 0, 0, -1),
            Vertex(vs.x, ve.y, 0, ts.x, -te.y, 1, 1, 1, 1, 0, 0, -1)
        );
        mVertexBuffer.commit();
    }
    else
    {
        //glm::vec2 inner_size = subrect.size * split9_factor;
        glm::vec2 offset_tl = subrect.size * splitMiddle.position;
        glm::vec2 offset_br = subrect.size * (glm::vec2(1, 1) - splitMiddle.position - splitMiddle.size);

        // Texture: Start/End Outer/Inner
        glm::vec2 tso = subrect.position;
        glm::vec2 teo = (subrect.position + subrect.size);
        glm::vec2 tsi = tso + offset_tl;
        glm::vec2 tei = teo - offset_br;

        // Vertex: Start/End Outer/Inner
        glm::vec2 vso(0, 0);
        glm::vec2 veo = size;
        glm::vec2 vsi = vso + offset_tl * tex_size;
        glm::vec2 vei = veo - offset_br * tex_size;

        mVertexBuffer.clear();

        // Center
        mVertexBuffer.addQuad(
            Vertex(vsi.x, vsi.y, 0, tsi.x, -tsi.y),
            Vertex(vei.x, vsi.y, 0, tei.x, -tsi.y),
            Vertex(vei.x, vei.y, 0, tei.x, -tei.y),
            Vertex(vsi.x, vei.y, 0, tsi.x, -tei.y)
        );

        // Left
        mVertexBuffer.addQuad(
            Vertex(vso.x, vsi.y, 0, tso.x, -tsi.y),
            Vertex(vsi.x, vsi.y, 0, tsi.x, -tsi.y),
            Vertex(vsi.x, vei.y, 0, tsi.x, -tei.y),
            Vertex(vso.x, vei.y, 0, tso.x, -tei.y)
        );

        // Right
        mVertexBuffer.addQuad(
            Vertex(vei.x, vsi.y, 0, tei.x, -tsi.y),
            Vertex(veo.x, vsi.y, 0, teo.x, -tsi.y),
            Vertex(veo.x, vei.y, 0, teo.x, -tei.y),
            Vertex(vei.x, vei.y, 0, tei.x, -tei.y)
        );

        // Top
        mVertexBuffer.addQuad(
            Vertex(vsi.x, vso.y, 0, tsi.x, -tso.y),
            Vertex(vei.x, vso.y, 0, tei.x, -tso.y),
            Vertex(vei.x, vsi.y, 0, tei.x, -tsi.y),
            Vertex(vsi.x, vsi.y, 0, tsi.x, -tsi.y)
        );

        // Bottom
        mVertexBuffer.addQuad(
            Vertex(vsi.x, vei.y, 0, tsi.x, -tei.y),
            Vertex(vei.x, vei.y, 0, tei.x, -tei.y),
            Vertex(vei.x, veo.y, 0, tei.x, -teo.y),
            Vertex(vsi.x, veo.y, 0, tsi.x, -teo.y)
        );

        // Top-Left
        mVertexBuffer.addQuad(
            Vertex(vso.x, vso.y, 0, tso.x, -tso.y),
            Vertex(vsi.x, vso.y, 0, tsi.x, -tso.y),
            Vertex(vsi.x, vsi.y, 0, tsi.x, -tsi.y),
            Vertex(vso.x, vsi.y, 0, tso.x, -tsi.y)
        );

        // Top-Right
        mVertexBuffer.addQuad(
            Vertex(vei.x, vso.y, 0, tei.x, -tso.y),
            Vertex(veo.x, vso.y, 0, teo.x, -tso.y),
            Vertex(veo.x, vsi.y, 0, teo.x, -tsi.y),
            Vertex(vei.x, vsi.y, 0, tei.x, -tsi.y)
        );

        // Bottom-Left
        mVertexBuffer.addQuad(
            Vertex(vso.x, vei.y, 0, tso.x, -tei.y),
            Vertex(vsi.x, vei.y, 0, tsi.x, -tei.y),
            Vertex(vsi.x, veo.y, 0, tsi.x, -teo.y),
            Vertex(vso.x, veo.y, 0, tso.x, -teo.y)
        );

        // Bottom-Right
        mVertexBuffer.addQuad(
            Vertex(vei.x, vei.y, 0, tei.x, -tei.y),
            Vertex(veo.x, vei.y, 0, teo.x, -tei.y),
            Vertex(veo.x, veo.y, 0, teo.x, -teo.y),
            Vertex(vei.x, veo.y, 0, tei.x, -teo.y)
        );
        mVertexBuffer.commit();
    }

}

void Shape2D::setMaterial(std::shared_ptr<Material> mat)
{
    mMaterial = mat;
}

std::shared_ptr<Material> Shape2D::getMaterial()
{
    return mMaterial;
}

void Shape2D::draw()
{
    mVertexBuffer.draw();
}
