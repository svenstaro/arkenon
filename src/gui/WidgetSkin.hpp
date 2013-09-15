#ifndef _GUI_WIDGETSKIN_HPP
#define _GUI_WIDGETSKIN_HPP

#include <map>

#include "gui/TextureSubrect.hpp"

struct WidgetSkin {
public:
    enum State {
        Normal,
        Focus,
        Active,
        Disabled
    };

public:
    WidgetSkin();

    void setTextureSubrect(const TextureSubrect& texture_subrect);
    void setTextureSubrect(State state, const TextureSubrect& texture_subrect);
    const TextureSubrect& getTextureSubrect(State state) const;

    void setTextColor(const glm::vec4& color);
    void setTextColor(State state, const glm::vec4& color);
    const glm::vec4& getTextColor(State state) const;

    std::map<State, TextureSubrect> mSubrects;
    std::map<State, glm::vec4> mTextColors;
};

#endif
