#ifndef _GUI_BUTTON_HPP
#define _GUI_BUTTON_HPP

#include <map>

#include "gui/Widget.hpp"
#include "render/Shape2D.hpp"
#include "gui/Label.hpp"
#include "scene/Mesh.hpp"
#include "util/Rect.hpp"

class Button : public Widget {
public:
    Button(const std::string& name, const std::string& text = "");

    // label
    void setFontSize(int font_size);
    void setText(const std::string& text);
    void setFont(std::shared_ptr<Font> font);
    void setColor(const glm::vec4& color);

    void onPrepareRender();

    bool isFocusable() const;

private:
    std::shared_ptr<Shape2D> mShape;
    std::shared_ptr<Text> mText;

};

#endif
