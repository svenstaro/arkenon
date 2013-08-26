#ifndef _RENDER_FONTPAGE_HPP
#define _RENDER_FONTPAGE_HPP

#include <memory>
#include <string>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <FreeImagePlus.h>

#include "render/Texture.hpp"
#include "Rect.hpp"

class FontPage {
public:
    struct Glyph {
    public:
        typedef char32_t CharType;
        Glyph() {}
        Glyph(Rect _subrect, glm::vec2 _size, int _y_offset, int _x_advance)
            : subrect(_subrect), size(_size), yOffset(_y_offset), xAdvance(_x_advance) {}
        Rect subrect;   //< 0|0 .. 1|1 subrect in font texture
        glm::vec2 size; //< pixel size of glyph
        int yOffset;    //< how much from the top we shall offset the vertices (in pixels)
        int xAdvance;   //< how much to offset the pen after writing
    };

public:
    FontPage(unsigned int size, FT_Face face);
    std::shared_ptr<Texture> getTexture();
    void ensureCharactersAvailable(std::string chars);
    void addCharacter(Glyph::CharType character);
    const Glyph& getGlyph(Glyph::CharType unicode);
    int getTextWidth(std::string text);

private:
    FT_GlyphSlot render(Glyph::CharType unicode, bool loadOnly = false);

    FT_Face mFace;
    unsigned int mSize;

    std::map<Glyph::CharType, Glyph> mGlyphs;
    fipImage mImage;
    bool mNeedsTextureUpdate;
    std::shared_ptr<Texture> mTexture;

};

#endif
