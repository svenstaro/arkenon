#ifndef _GUI_LABEL_HPP
#define _GUI_LABEL_HPP

#include "gui/Widget.hpp"
#include "render/Text.hpp"

class Label : public Widget {
public:
    Label(const std::string& text = "",
          std::shared_ptr<Font> font = Font::defaultFont,
          int font_size = Font::defaultSize,
          const glm::vec4& color = glm::vec4(1, 1, 1, 1));

    void setFontSize(int font_size);
    void setText(const std::string& text);
    void setFont(std::shared_ptr<Font> font);
    void setColor(const glm::vec4& color);

    void render(std::shared_ptr<Camera> camera, std::shared_ptr<ShaderProgram> shader_program);

protected:
    std::shared_ptr<Text> mText;

};

#endif
