#include "Text.hpp"

#include "util/Utf8Iterator.hpp"

Text::Text(const std::string& name, const std::string& text, std::shared_ptr<Font> font, int font_size, const glm::vec4& color)
    : Node(name),
      mFont(font),
      mText(text),
      mFontSize(font_size),
      mColor(color)
{
    setAlign(Center, Center);
    recreateBuffer();
}

void Text::setFont(std::shared_ptr<Font> font)
{
    mFont = font;
    recreateBuffer();
}

void Text::setText(const std::string& text)
{
    mText = text;
    recreateBuffer();
}

void Text::setFontSize(int font_size)
{
    mFontSize = font_size;
    recreateBuffer();
}

void Text::setColor(const glm::vec4& color)
{
    mColor = color;
    recreateBuffer();
}

void Text::setAlign(Text::Align vertical, Align horizontal)
{
    mVerticalAlign = vertical;
    mHorizontalAlign = horizontal;
    recreateBuffer();
}

void Text::recreateBuffer()
{
    std::shared_ptr<FontPage> page = mFont->getPage(mFontSize);
    page->ensureCharactersAvailable(mText);

    mVertexBuffer.clear();

    glm::vec2 offset(0, 0);
    if(mVerticalAlign != Text::Start) {
        int width = page->getTextWidth(mText);
        offset.x = (mVerticalAlign == Text::End ? -width : -width/2);
    }
    if(mHorizontalAlign != Text::End) {
        offset.y = (mVerticalAlign == Text::Start ? mFontSize : mFontSize/2);
    }


    for(Utf8Iterator i(mText.begin()); i != mText.end(); ++i) {
        FontPage::Glyph g = page->getGlyph(*i);

        glm::vec2 vs = offset + glm::vec2(0, -g.yOffset);  // vertex start
        glm::vec2 ve = vs + g.size;                     // vertex end
        glm::vec2 ts = g.subrect.position;              // texture start
        glm::vec2 te = ts + g.subrect.size;             // texture end

        mVertexBuffer.addQuad(
                    Vertex(vs.x, -vs.y, 0, ts.x, -ts.y, mColor.r, mColor.g, mColor.b, mColor.a),
                    Vertex(vs.x, -ve.y, 0, ts.x, -te.y, mColor.r, mColor.g, mColor.b, mColor.a),
                    Vertex(ve.x, -ve.y, 0, te.x, -te.y, mColor.r, mColor.g, mColor.b, mColor.a),
                    Vertex(ve.x, -vs.y, 0, te.x, -ts.y, mColor.r, mColor.g, mColor.b, mColor.a)
                    );

        offset.x = offset.x + g.xAdvance;
    }

    mVertexBuffer.commit();
}

void Text::render(std::shared_ptr<Camera> camera, std::shared_ptr<ShaderProgram> shader_program)
{
    glm::mat4 MVP = camera->getViewProjectionMatrix() * getAbsoluteTransformationMatrix();
    shader_program->send("MVP", MVP);
    shader_program->send("diffuse_texture", mFont->getPage(mFontSize)->getTexture(), 0);
    mVertexBuffer.draw();
}
