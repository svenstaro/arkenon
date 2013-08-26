#ifndef _GUI_BUTTON_HPP
#define _GUI_BUTTON_HPP

#include <map>

#include "gui/Widget.hpp"
#include "render/Shape2D.hpp"
#include "gui/Label.hpp"
#include "scene/Mesh.hpp"
#include "util/Rect.hpp"

class Button : public Label {
public:
    enum State {
        Normal,
        Hover,
        Focus,
        Active
    };

public:
    Button(const std::string& text = "");

    // background
    void setTexture(std::shared_ptr<Texture> texture);
    void setSubrect(State state, const Rect& subrect);

    // label
    void setFontSize(int font_size);
    void setText(const std::string& text);
    void setFont(std::shared_ptr<Font> font);
    void setColor(const glm::vec4& color);

    void render(std::shared_ptr<Camera> camera, std::shared_ptr<ShaderProgram> shader_program);

    void onMouseMoved(double x, double y);
    void onMouseButtonPressed(int button, int mods);
    void onMouseButtonReleased(int button, int mods);
    bool isHover(const glm::vec2& pos);

private:
    std::shared_ptr<Shape2D> mShape;
    std::shared_ptr<Text> mText;
    Rect mSubrect;
    State mState;
    std::map<State, Rect> mSubrects;

};

#endif
