#ifndef _GUI_BUTTON_HPP
#define _GUI_BUTTON_HPP

#include <map>

#include "gui/Widget.hpp"
#include "render/Shape2D.hpp"
#include "scene/Mesh.hpp"
#include "Rect.hpp"

class Button : public Widget {
public:
    enum State {
        Normal,
        Hover,
        Focus,
        Active
    };

public:
    Button(const std::string& title = "");

    void setTexture(std::shared_ptr<Texture> texture);
    void setSubrect(State state, const Rect& subrect);

    void render(std::shared_ptr<Camera> camera, std::shared_ptr<ShaderProgram> shader_program);

    void onMouseMoved(double x, double y);

    bool isHover(const glm::vec2& pos);

private:
    std::string mTitle;
    std::shared_ptr<Shape2D> mShape;
    Rect mSubrect;
    State mState;
    std::map<State, Rect> mSubrects;

};

#endif
