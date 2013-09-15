#include "WidgetSkin.hpp"

WidgetSkin::WidgetSkin()
{}

void WidgetSkin::setTextureSubrect(const TextureSubrect& texture_subrect)
{
    setTextureSubrect(WidgetSkin::Normal, texture_subrect);
    setTextureSubrect(WidgetSkin::Active, texture_subrect);
    setTextureSubrect(WidgetSkin::Focus, texture_subrect);
    setTextureSubrect(WidgetSkin::Disabled, texture_subrect);
}

void WidgetSkin::setTextureSubrect(State state, const TextureSubrect& texture_subrect)
{
    mSubrects[state] = texture_subrect;
}

const TextureSubrect& WidgetSkin::getTextureSubrect(State state) const
{
    return mSubrects.at(state);
}

void WidgetSkin::setTextColor(const glm::vec4& color)
{
    setTextColor(WidgetSkin::Normal, color);
    setTextColor(WidgetSkin::Active, color);
    setTextColor(WidgetSkin::Focus, color);
    setTextColor(WidgetSkin::Disabled, color);
}

void WidgetSkin::setTextColor(State state, const glm::vec4& color)
{
    mTextColors[state] = color;
}

const glm::vec4&WidgetSkin::getTextColor(State state) const
{
    return mTextColors.at(state);
}
