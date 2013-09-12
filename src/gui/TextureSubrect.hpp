#ifndef _GUI_TEXTURESUBRECT_HPP
#define _GUI_TEXTURESUBRECT_HPP

#include <memory>

#include "render/Texture.hpp"
#include "util/Rect.hpp"

struct TextureSubrect {
public:
    TextureSubrect(std::shared_ptr<Texture> _texture = nullptr, Rect _subrect = Rect(0, 0, 1, 1))
        : texture(_texture), subrect(_subrect) {}

    std::shared_ptr<Texture> texture;
    Rect subrect;
};

#endif
