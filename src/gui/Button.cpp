#include "Button.hpp"

Button::Button(const std::string& title)
    : mTitle(title),
      mShape(new Shape2D("button-shape")),
      mState(Normal)
{
    addChild(mShape);
    setSubrect(Normal, Rect(0, 0, 1, 1));
    setSubrect(Hover, Rect(0, 0, 1, 1));
    setSubrect(Focus, Rect(0, 0, 1, 1));
    setSubrect(Active, Rect(0, 0, 1, 1));
}

void Button::setTexture(std::shared_ptr<Texture> texture)
{
    mShape->setTexture(texture);
}

void Button::setSubrect(Button::State state, const Rect& subrect)
{
    mSubrects[state] = subrect;
}

void Button::render(std::shared_ptr<Camera> camera, std::shared_ptr<ShaderProgram> shader_program)
{
    mShape->makeRectangle(mSize, mSubrects[mState], 0.33f);
    mShape->render(camera, shader_program);
}

void Button::onMouseMoved(double x, double y)
{
    mState = Normal;
    //TODO: camera projection
    glm::vec4 lm = glm::inverse(getAbsoluteTransformationMatrix()) * glm::vec4(x, y, 0.f, 1.f);
    if(lm.x >= 0 && lm.y >= 0 && lm.x <= mSize.x && lm.y <= mSize.y) {
        mState = Hover;
    }
}

bool Button::isHover(const glm::vec2& pos)
{
}
