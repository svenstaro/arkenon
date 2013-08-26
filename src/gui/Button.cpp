#include "Button.hpp"

Button::Button(const std::string& text)
    : mShape(new Shape2D("button-shape")),
      mText(new Text("button-shape", text)),
      mState(Normal),
      mSplit9Factor(0.33f, 0.33f)
{
    addChild(mShape);
    addChild(mText);

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

void Button::setSplit9Factor(const glm::vec2& split9_factor)
{
    mSplit9Factor = split9_factor;
}

void Button::setFontSize(int font_size)
{
    mText->setFontSize(font_size);
}

void Button::setText(const std::string& text)
{
    mText->setText(text);
}

void Button::setFont(std::shared_ptr<Font> font)
{
    mText->setFont(font);
}

void Button::setColor(const glm::vec4& color)
{
    mText->setColor(color);
}

void Button::render(std::shared_ptr<Camera> camera, std::shared_ptr<ShaderProgram> shader_program)
{
    mText->position = glm::vec3(mSize.x * 0.5f, mSize.y * 0.5f, 1.f);

    mShape->makeRectangle(mSize, mSubrects[mState], mSplit9Factor);
    mShape->render(camera, shader_program);
    mText->render(camera, shader_program);
}

void Button::onEvent(const Event* event)
{
    switch(event->type) {
        case Event::MouseMove:
            if(mState == Active) break;
            mState = isHover(((MouseMoveEvent*)event)->position) ? Hover : Normal;
            break;
        case Event::MousePress:
            if(isHover(((MousePressEvent*)event)->position))
                mState = Active;
            break;
        case Event::MouseRelease:
            if(mState == Active && isHover(((MouseReleaseEvent*)event)->position))
            {
                //std::cout << "click" << std::endl;
                mState = Hover;
            }
            else
            {
                mState = Normal;
            }
            break;
    }
}

bool Button::isHover(const glm::vec2& pos)
{
    //TODO: camera projection
    glm::vec4 lm = glm::inverse(getAbsoluteTransformationMatrix()) * glm::vec4(pos.x, pos.y, 0.f, 1.f);
    return lm.x >= 0 && lm.y >= 0 && lm.x <= mSize.x && lm.y <= mSize.y;
}

Button::State Button::getState() const
{
    return mState;
}
