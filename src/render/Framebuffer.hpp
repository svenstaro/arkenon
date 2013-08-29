#ifndef _RENDER_FRAMEBUFFER_HPP
#define _RENDER_FRAMEBUFFER_HPP

#include <GL/glew.h>

#include <memory>
#include <vector>

#include "render/Texture.hpp"
#include "render/RenderTarget.hpp"

class Framebuffer : public RenderTarget {
public:
    Framebuffer(glm::vec2 size, int mrt_count = 1, GLenum texture_mode = GL_RGB);

    void bind();
    static void unbind(int mode = GL_FRAMEBUFFER);
    void bindDraw(int num = 1, int* buffers = 0);
    void bindRead(int number = 1);

    std::shared_ptr<Texture> getTexture(int target = 0);
    GLuint getHandle(int target = 0);

private:
    int mMrtCount;
    GLuint mHandle;
    std::vector<std::shared_ptr<Texture>> mTextures;
    GLuint mDepthbuffer;

};

#endif
