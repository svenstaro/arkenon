#ifndef _RENDER_TEXTURE_HPP
#define _RENDER_TEXTURE_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <FreeImagePlus.h>

#include "util/Random.hpp"

class Texture {
public:
    /**
     * Initializes a texture.
     */
    Texture();

    /**
     * Initializes and loads a texture.
     */
    Texture(const std::string& filename);

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
     * Creates a texture with random data.
     * @param size The size for the random texture.
     */
    void random(unsigned int seed, const glm::vec2& size = glm::vec2(32, 32));

    /**
     * Creates an empty texture.
     * @param size The size for the empty texture.
     */
    void create(const glm::vec2& size, GLenum type = GL_RGB, GLenum secondtype = GL_RGB, GLenum precision = GL_UNSIGNED_INT, void* data = 0);

    /**
     * Sets the mipmap mode.
     * @param mipmap Whether to mipmap or not.
     */
    void setMipmap(bool mipmap);

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

    /**
     * Returns an empty (white) 1x1 pixel texture as default texture when none is provided.
     */
    static std::shared_ptr<Texture> empty();

private:
    void updateTexParameters();
    void generateMipmap();

    GLuint mHandle;
    glm::vec2 mSize;
    bool mSmooth;
    bool mMipmap;

    bool mMipmapsGenerated;
    bool mTextureLoaded;

    static std::shared_ptr<Texture> _empty;
};

#endif
