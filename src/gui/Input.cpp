#include "Input.hpp"

Input::Input(const std::string& name, const std::string& text)
    : Widget(name),
      mShape(new Shape2D("input:shape")),
      mText(new Text("input:text", text))
{
    setText(text);
    addChild(mShape);
    addChild(mText);
}

void Input::setText(const std::string& text)
{
    mValue = text;
    mText->setText(text);
}

const std::string&Input::getText() const
{
    return mValue;
}

void Input::onPrepareRender()
{
    auto t = mSkin->getTextureSubrect(mState);
    std::shared_ptr<Material> m = std::make_shared<Material>();
    m->setDiffuseTexture(t.texture);
    mShape->setMaterial(m);
    mShape->makeRectangle(mSize, t.subrect, t.splitMiddle);

    mText->setAlign(Text::Start, Text::Center);
    mText->position = glm::vec3(0, mSize.y * 0.5f, 1.f);
}

void Input::onEvent(const Event* event)
{
    Widget::onEvent(event);

    if(!isFocused()) return;

    int key;
    switch(event->type) {
        case Event::Character:
            mValue += (char)((CharacterEvent*)event)->unicode;
            break;
        case Event::KeyPress:
            key = ((KeyPressEvent*)event)->key;
            if(key == GLFW_KEY_BACKSPACE)
                mValue = mValue.substr(0, mValue.length() - 1);
            break;
        default:
            return;
    }
    setText(mValue);
}

bool Input::isFocusable() const
{
    return true;
}
