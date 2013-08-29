#include "FontPage.hpp"

#include "util/check.hpp"
#include "util/Utf8Iterator.hpp"


#include <iostream>

FontPage::FontPage(unsigned int size, FT_Face face)
    : mFace(face),
      mSize(size),
      mTexture(std::make_shared<Texture>()),
      mMaterial(std::make_shared<Material>())
{
    // get next power of 2
    unsigned int pot = 1;
    while (pot < size*16) pot *= 2;

    mImage = fipImage(FIT_BITMAP, pot, pot, 32);
    mTexture->create(glm::vec2(pot, pot));

    mMaterial->setDiffuseTexture(mTexture);

}

std::shared_ptr<Material> FontPage::getMaterial()
{
    if(mNeedsTextureUpdate)
    {
        mTexture->load(mImage);
        mTexture->setSmooth(false);
        mNeedsTextureUpdate = false;
    }
    return mMaterial;
}

void FontPage::ensureCharactersAvailable(std::string chars)
{
    for(Utf8Iterator i(chars.begin()); i != chars.end(); ++i)
        addCharacter(*i);
}

void FontPage::addCharacter(Glyph::CharType character)
{
    if(mGlyphs.count(character) > 0) return;

    // set font size for this rendering task
    FT_CHECK(FT_Set_Pixel_Sizes(mFace, 0, mSize));

    // render the glyph
    render(character);
    FT_Bitmap bitmap = mFace->glyph->bitmap;

    // find a place on the image for our glyph
    // the image is divided into squares of size ```mSize x mSize```
    // so the new glyph starts at:
    int id = mGlyphs.size();
    int square = mImage.getWidth() / mSize;
    int x = (id % square) * mSize;
    int y = (id / square) * mSize;

    // Create the rectangle
    Glyph glyph(Rect(x * 1.f / mImage.getWidth(),
                     y * 1.f / mImage.getHeight(),
                     bitmap.width * 1.f / mImage.getWidth(),
                     bitmap.rows * 1.f / mImage.getHeight()),
                glm::vec2(bitmap.width, bitmap.rows),
                mFace->glyph->bitmap_top,
                mFace->glyph->advance.x / 64);

    // TODO: Optimize this, I don't believe we have to manually copy all the pixels
    for(int i = 0; i < bitmap.width * bitmap.rows; ++i) {
        unsigned char c = *(bitmap.buffer + i);
        RGBQUAD q;
        q.rgbRed = 255;
        q.rgbGreen = 255;
        q.rgbBlue = 255;
        q.rgbReserved = c;
        mImage.setPixelColor(x + i % bitmap.width, mImage.getHeight() - (y + 1 + i / bitmap.width), &q);
        // I do not know why the `1` is required here, but it somehow is...  ^   :P
    }

    mGlyphs[character] = glyph;

    mNeedsTextureUpdate = true;
}

const FontPage::Glyph&FontPage::getGlyph(FontPage::Glyph::CharType unicode)
{
    return mGlyphs[unicode];
}

int FontPage::getTextWidth(std::string text)
{
    int width = 0;
    for(Utf8Iterator i(text.begin()); i != text.end(); ++i) {
        FontPage::Glyph g = getGlyph(*i);
        width += g.xAdvance;
        if(i == text.end() - 1)
        {
            width -= g.xAdvance;
            width += g.size.x;
        }
    }
    return width;
}

FT_GlyphSlot FontPage::render(Glyph::CharType unicode, bool loadOnly) {
    FT_CHECK(FT_Load_Glyph(mFace, FT_Get_Char_Index(mFace, unicode), FT_LOAD_DEFAULT));
    if(!loadOnly && mFace->glyph->format != FT_GLYPH_FORMAT_BITMAP) {
        FT_CHECK(FT_Render_Glyph(mFace->glyph, FT_RENDER_MODE_NORMAL));
    }
    return mFace->glyph;
}

