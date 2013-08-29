#include "Label.hpp"

Label::Label(const std::string& text, std::shared_ptr<Font> font, int font_size, const glm::vec4& color)
    : mText(std::make_shared<Text>("text-widget", text, font, font_size, color))
{
    addChild(mText);
}

void Label::setFontSize(int font_size)
{
    mText->setFontSize(font_size);
}

void Label::setText(const std::string& text)
{
    mText->setText(text);
}

void Label::setFont(std::shared_ptr<Font> font)
{
    mText->setFont(font);
}

void Label::setColor(const glm::vec4& color)
{
    mText->setColor(color);
}

std::shared_ptr<Texture> Label::getDiffuseTexture()
{
    return mText->getDiffuseTexture();
}

void Label::draw()
{
    mText->draw();
}
