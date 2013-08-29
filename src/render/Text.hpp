#ifndef _RENDER_TEXT_HPP
#define _RENDER_TEXT_HPP

#include <memory>

#include "render/Font.hpp"
#include "render/VertexBuffer.hpp"
#include "render/Renderable.hpp"
#include "scene/Node.hpp"

class Text : public RenderableNode {
public:
    enum Align {
        Start,
        Center,
        End
    };

public:
    Text(const std::string& name,
         const std::string& text = "",
         std::shared_ptr<Font> font = Font::defaultFont,
         int font_size = Font::defaultSize,
         const glm::vec4& color = glm::vec4(1, 1, 1, 1));

    void setFont(std::shared_ptr<Font> font);
    void setText(const std::string& text);
    void setFontSize(int font_size);
    void setColor(const glm::vec4& color);
    void setAlign(Align vertical, Align horizontal);

    std::shared_ptr<Material> getMaterial();
    void draw();

private:
    void recreateBuffer();

    VertexBuffer mVertexBuffer;
    std::shared_ptr<Font> mFont;
    std::string mText;
    int mFontSize;
    glm::vec4 mColor;

    Align mVerticalAlign;
    Align mHorizontalAlign;

};

#endif
