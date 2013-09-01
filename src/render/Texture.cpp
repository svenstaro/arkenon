#include "Texture.hpp"
#include "util/check.hpp"

#include <iostream>

std::shared_ptr<Texture> Texture::_empty;

Texture::Texture()
    : mMipmapsGenerated(false),
      mTextureLoaded(false)
{
    glGenTextures(1, &mHandle);
    GL_CHECK();

    setMipmap(false);
    setSmooth(true);
}

Texture::Texture(const std::string& filename)
    : Texture()
{
    load(filename);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, mHandle);
    GL_CHECK();
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    GL_CHECK();
}

void Texture::random(unsigned int seed, const glm::vec2& size) {
    bind();
    mSize = size;

    Random rng(seed);

    std::vector<float> charBuffer;
    charBuffer.resize(size.x * size.y * 3);

    rng.fillWithRandom(size.x * size.y * 3, charBuffer);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mSize.x, mSize.y, 0, GL_RGB, GL_FLOAT, &charBuffer[0]);
    GL_CHECK();
}


void Texture::load(const fipImage& image)
{
    int bpp = image.getBitsPerPixel();
    int type = image.getImageType();

    mSize = glm::vec2(image.getWidth(), image.getHeight());

    bind();
    if(type == FIT_BITMAP && bpp == 24)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mSize.x, mSize.y, 0, GL_BGR, GL_UNSIGNED_BYTE, (void*)image.accessPixels());
    else if(type == FIT_BITMAP && bpp == 32)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mSize.x, mSize.y, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)image.accessPixels());
    else
        std::cerr << "Invalid internal image format or bpp." << std::endl;;
    GL_CHECK();

    mTextureLoaded = true;
    mMipmapsGenerated = false;

    generateMipmap();
}

void Texture::load(const std::string& filename)
{
    fipImage image;
    image.load(filename.c_str(), 0);
    load(image);
}

void Texture::create(const glm::vec2& size, GLenum type, GLenum secondtype, void* data)
{
    bind();
    mSize = size;
    glTexImage2D(GL_TEXTURE_2D, 0, type, mSize.x, mSize.y, 0, secondtype, GL_UNSIGNED_BYTE, data);
    GL_CHECK();

    mTextureLoaded = true;
    mMipmapsGenerated = false;

    generateMipmap();
}

void Texture::setMipmap(bool mipmap)
{
    mMipmap = mipmap;
    updateTexParameters();
    if(mipmap) generateMipmap();
}

void Texture::setSmooth(bool smooth)
{
    mSmooth = smooth;
    updateTexParameters();
}

void Texture::updateTexParameters()
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mSmooth ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mSmooth ? (mMipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR) : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    GL_CHECK();
}

void Texture::generateMipmap()
{
    // only generate if a texture is loaded, we did not generate them yet, and mipmapping is on
    if(!mTextureLoaded || mMipmapsGenerated || !mMipmap) return;

    bind();
    glGenerateMipmap(GL_TEXTURE_2D);
    GL_CHECK();
    mMipmapsGenerated = true;
}

GLuint Texture::getHandle() const
{
    return mHandle;
}

const glm::vec2&Texture::getSize() const
{
    return mSize;
}

std::shared_ptr<Texture> Texture::empty()
{
    if(!_empty)
    {
        _empty = std::make_shared<Texture>();
        char data[3] = {255, 255, 255};
        _empty->create(glm::vec2(1, 1), GL_RGB, GL_RGB, (void*)data);
    }
    return _empty;
}
