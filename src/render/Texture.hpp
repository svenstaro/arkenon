#ifndef _RENDER_TEXTURE_HPP
#define _RENDER_TEXTURE_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <FreeImagePlus.h>

class Texture {
public:
    /**
     * Initializes a texture.
     */
    Texture();

    /**
     * Binds this Texture for OpenGL operations.
     */
    void bind();

    static void unbind();

    /**
     * Loads a texture from a bitmap.
     * @param filename The bitmap.
     */
    void load(const fipImage& image);

    /**
     * Loads a texture from an image file.
     * @param filename The path to the image file.
     */
    void load(const std::string& filename);

    /**
     * Creates an empty texture.
     * @param size The size for the empty texture.
     */
    void create(const glm::vec2& size, GLenum type = GL_RGB);

    /**
     * Sets the filtering of a texture.
     * @param smooth If true, GL_LINEAR filtering is used, GL_NEAREST otherwise.
     */
    void setSmooth(bool smooth = true);

    /**
     * Returns the OpenGL handle of this texture for direct access.
     * @return The OpenGL texture id.
     */
    GLuint getHandle() const;

    /**
     * Returns the size of the texture.
     * @return The texture size.
     */
    const glm::vec2& getSize() const;

private:
    GLuint mHandle;
    glm::vec2 mSize;

};

#endif
