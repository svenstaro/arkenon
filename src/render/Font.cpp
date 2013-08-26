#include "Font.hpp"

#include "util/check.hpp"

FT_Library Font::library;
bool Font::libraryInitialized = false;
std::shared_ptr<Font> Font::defaultFont = nullptr;
int Font::defaultSize = 12;

Font::Font(const std::string& file)
{
    if(!libraryInitialized && FT_CHECK(FT_Init_FreeType(&library)))
        libraryInitialized = true;

    FT_CHECK(FT_New_Face(library, file.c_str(), 0, &mFace));
}

std::shared_ptr<FontPage> Font::getPage(unsigned int size)
{
    if(mPages.count(size) <= 0)
    {
        mPages.emplace(size, std::make_shared<FontPage>(size, mFace));
    }

    return mPages[size];
}
