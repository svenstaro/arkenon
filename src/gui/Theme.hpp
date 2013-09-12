#ifndef _GUI_THEME_HPP
#define _GUI_THEME_HPP

#include <map>

#include "gui/Widget.hpp"
#include "gui/TextureSubrect.hpp"

struct Theme {
public:
    enum Themables {
        Button,
    };

public:
    WidgetSkin();

    void setTextureSubrect(Widget::State state, TextureSubrect texture_subrect);
    const TextureSubrect& getTextureSubrect(Widget::State state) const;

    std::map<Widget::State, TextureSubrect> mSubrects;
};

#endif
