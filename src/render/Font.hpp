#ifndef _RENDER_FONT_HPP
#define _RENDER_FONT_HPP

#include <string>
#include <map>
#include <memory>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <FreeImagePlus.h>

#include "render/Texture.hpp"
#include "render/FontPage.hpp"

class Font {
public:
    Font(const std::string& file);
    std::shared_ptr<FontPage> getPage(unsigned int size);

private:
    FT_Face mFace;
    std::map<unsigned int, std::shared_ptr<FontPage>> mPages;

public:
    static FT_Library  library;
    static bool libraryInitialized;
    static std::shared_ptr<Font> defaultFont;
    static int defaultSize;
};

#endif
