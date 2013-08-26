#include "Shape2D.hpp"

Shape2D::Shape2D(const std::string& name)
    : Node(name)
{}

void Shape2D::makeRectangle(const glm::vec2& size, const Rect& subrect, const glm::vec2& split9_factor, const glm::vec2& texture_size)
{
    glm::vec2 tex_size = texture_size;
    if(tex_size.x == 0 && tex_size.y == 0)
    {
        if(mTexture)
        {
            tex_size = mTexture->getSize();
        }
        else
        {
            std::cerr << "Set a texture or provide a texture_size for makeRectangle()." << std::endl;
            return;
        }
    }

    if(split9_factor.x >= 1.f && split9_factor.y >= 1.f)
    {
        // Texture: Start/End
        glm::vec2 ts = subrect.position;
        glm::vec2 te = (subrect.position + subrect.size);

        // Vertex: Start/End
        glm::vec2 vs(0, 0);
        glm::vec2 ve = size;

        mVertexBuffer.clear();
        mVertexBuffer.addQuad(
            Vertex(vs.x, vs.y, 0, ts.x, -ts.y),
            Vertex(ve.x, vs.y, 0, te.x, -ts.y),
            Vertex(ve.x, ve.y, 0, te.x, -te.y),
            Vertex(vs.x, ve.y, 0, ts.x, -te.y)
        );
        mVertexBuffer.commit();
    }
    else
    {
        //glm::vec2 inner_size = subrect.size * split9_factor;
        glm::vec2 inner_offset = subrect.size * (glm::vec2(1.f, 1.f) - split9_factor) * 0.5f;
        glm::vec2 pixel_offset = inner_offset * tex_size;

        // Texture: Start/End Outer/Inner
        glm::vec2 tso = subrect.position;
        glm::vec2 teo = (subrect.position + subrect.size);
        glm::vec2 tsi = tso + inner_offset;
        glm::vec2 tei = teo - inner_offset;

        // Vertex: Start/End Outer/Inner
        glm::vec2 vso(0, 0);
        glm::vec2 veo = size;
        glm::vec2 vsi = vso + pixel_offset;
        glm::vec2 vei = veo - pixel_offset;

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

void Shape2D::setTexture(std::shared_ptr<Texture> texture)
{
    mTexture = texture;
}

void Shape2D::render(std::shared_ptr<Camera> camera, std::shared_ptr<ShaderProgram> shader_program)
{
    glm::mat4 MVP = camera->getViewProjectionMatrix() * getAbsoluteTransformationMatrix();
    shader_program->send("MVP", MVP);
    shader_program->send("diffuse_texture", mTexture, 0);
    mVertexBuffer.draw();
}
