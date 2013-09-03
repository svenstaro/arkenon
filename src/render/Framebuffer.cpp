#include "Framebuffer.hpp"

#include "util/check.hpp"
#include <iostream>
#include <new>

void checkFramebuffer() {
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if(status != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer not complete: " << std::hex << status << std::endl;
    }
}

Framebuffer::Framebuffer(glm::vec2 size, int mrt_count, bool depth, GLenum texture_mode, GLenum sectype, GLenum precision)
    : RenderTarget(size),
      mMrtCount(mrt_count)
{
    glGenFramebuffersEXT(1, &mHandle);
    bind();

    // create the textures
    for(unsigned int i = 0; i < mrt_count; ++i) {
        std::shared_ptr<Texture> texture = std::make_shared<Texture>();
        texture->setSmooth(false);
        texture->create(getSize(), texture_mode, sectype, precision);
        texture->bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texture->getHandle(), 0);
        mTextures.push_back(texture);
    }
    GL_CHECK();

    checkFramebuffer();

    if(depth) {
        // create depth buffer

        mDepthTexture = std::make_shared<Texture>();
        mDepthTexture->setSmooth(false);
        mDepthTexture->create(getSize(), GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT);
        mDepthTexture->bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTexture->getHandle(), 0);
        /*
        glGenRenderbuffers(1, &mDepthbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, mDepthbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, getSize().x, getSize().y);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthbuffer);
        */
    }
    
    GL_CHECK();
}

void Framebuffer::bindDraw(int num, int* buffers)
{
    assert(num <= GL_MAX_COLOR_ATTACHMENTS);
    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mHandle);

    if(buffers == 0) {
        buffers = new int[num];
        for(int i = 0; i < num; ++i) buffers[i] = GL_COLOR_ATTACHMENT0 + i;
    } else {
        for(int i = 0; i < num; ++i) buffers[i] = GL_COLOR_ATTACHMENT0 + buffers[i];
    }

    glDrawBuffers(num, (GLenum*)buffers);
}

void Framebuffer::bindRead(int number)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mHandle);
    glReadBuffer(GL_COLOR_ATTACHMENT0 + number);
}

void Framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, mHandle);
}

void Framebuffer::unbind(int mode)
{
    glBindFramebuffer(mode, 0);
}

std::shared_ptr<Texture> Framebuffer::getTexture(int target)
{
    return mTextures[target];
}

std::shared_ptr<Texture> Framebuffer::getDepthTexture()
{
    return mDepthTexture;
}

GLuint Framebuffer::getHandle(int target)
{
    return mHandle + sizeof(GLuint) * target;
}
