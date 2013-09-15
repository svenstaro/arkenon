#ifndef _GUI_INPUT_HPP
#define _GUI_INPUT_HPP

#include "gui/Widget.hpp"
#include "render/Shape2D.hpp"
#include "render/Text.hpp"

class Input : public Widget {
public:
    Input(const std::string& name, const std::string& text = "");

    // label
    void setText(const std::string& text);
    const std::string& getText() const;

    void onPrepareRender();

    void onEvent(const Event* event);

    bool isFocusable() const;

private:
    std::shared_ptr<Shape2D> mShape;
    std::shared_ptr<Text> mText;

    std::string mValue;

};

#endif
