#include "Button.hpp"

Button::Button(const std::string& name, const std::string& text)
    : Widget(name),
      mShape(new Shape2D("button:shape")),
      mText(new Text("button:text", text))
{
    addChild(mShape);
    addChild(mText);
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
    mShape->makeRectangle(mSize, t.subrect, t.splitMiddle);

    mText->position = glm::vec3(mSize.x * 0.5f, mSize.y * 0.5f, 1.f);
}

bool Button::isFocusable() const
{
    return true;
}
