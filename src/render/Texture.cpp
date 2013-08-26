#include "Texture.hpp"
#include "util/check.hpp"

#include <iostream>

Texture::Texture()
{
    glGenTextures(1, &mHandle);
    GL_CHECK();
    setSmooth();
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, mHandle);
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
}

void Texture::load(const std::string& filename)
{
    fipImage image;
    image.load(filename.c_str(), 0);
    load(image);
}

void Texture::create(const glm::vec2& size)
{
    bind();
    mSize = size;
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, mSize.x, mSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
}

void Texture::setSmooth(bool smooth)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
    GL_CHECK();
}

GLuint Texture::getHandle() const
{
    return mHandle;
}

const glm::vec2&Texture::getSize() const
{
    return mSize;
}
