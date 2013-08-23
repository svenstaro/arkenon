#include "Framebuffer.hpp"

Framebuffer::Framebuffer(glm::vec2 size)
    : RenderTarget(size)
{
    glGenFramebuffers(1, &mHandle);

    setActive();

    // create Texture
    mTexture.create(mSize);
    mTexture.setSmooth(false);

    // create depth buffer
    glGenRenderbuffers(1, &mDepthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mSize.x, mSize.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthbuffer);

    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mTexture.getHandle(), 0);

    // Set the list of draw buffers.
    GLenum drawBuffers[2] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers); // "1" is the size of DrawBuffers
}

void Framebuffer::setActive()
{
    glBindFramebuffer(GL_FRAMEBUFFER, mHandle);
    glViewport(0, 0, mSize.x, mSize.y);
}

Texture* Framebuffer::getTexture()
{
    return &mTexture;
}
