#include "Button.hpp"

Button::Button(const std::string& name, const std::string& text)
    : Widget(name),
      mShape(new Shape2D("button:shape")),
      mText(new Text("button:text", text)),
      mState(WidgetSkin::Normal),
      mSplit9Factor(0.33f, 0.33f)
{
    addChild(mShape);
    addChild(mText);
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

void Button::onPrepareRender()
{
    auto t = mSkin->getTextureSubrect(mState);
    std::shared_ptr<Material> m = std::make_shared<Material>();
    m->setDiffuseTexture(t.texture);
    mShape->setMaterial(m);
    mShape->makeRectangle(mSize, t.subrect, mSplit9Factor);

    mText->position = glm::vec3(mSize.x * 0.5f, mSize.y * 0.5f, 1.f);
}

void Button::onEvent(const Event* event)
{
    switch(event->type) {
        case Event::MouseMove:
            if(mState == WidgetSkin::Active) break;
            mState = isHover(((MouseMoveEvent*)event)->position) ? WidgetSkin::Hover : WidgetSkin::Normal;
            break;
        case Event::MousePress:
            if(isHover(((MousePressEvent*)event)->position))
                mState = WidgetSkin::Active;
            break;
        case Event::MouseRelease:
            if(mState == WidgetSkin::Active && isHover(((MouseReleaseEvent*)event)->position))
            {
                //std::cout << "click" << std::endl;
                mState = WidgetSkin::Hover;
            }
            else
            {
                mState = WidgetSkin::Normal;
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

WidgetSkin::State Button::getState() const
{
    return mState;
}
