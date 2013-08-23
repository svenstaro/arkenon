#ifndef _RENDER_TEXTURE_HPP
#define _RENDER_TEXTURE_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <FreeImagePlus.h>

class Texture {
public:
    Texture();
    void bind();
    void load(const std::string& filename);
    void create(const glm::vec2& size);

    void setSmooth(bool smooth = true);

    GLuint getHandle() const;
    const glm::vec2& getSize() const;

private:
    GLuint mHandle;
    glm::vec2 mSize;

};

#endif
