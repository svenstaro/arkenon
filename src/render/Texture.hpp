#ifndef _RENDER_TEXTURE_HPP
#define _RENDER_TEXTURE_HPP

#include <GL/glew.h>
#include <string>
#include <FreeImagePlus.h>

class Texture {
public:
    Texture();
    void bind();
    void load(const std::string& filename);

    void setSmooth(bool smooth = true);

    GLuint getHandle() const;

private:
    GLuint mHandle;
};

#endif
