#ifndef _RENDER_SHADERPROGRAM_HPP
#define _RENDER_SHADERPROGRAM_HPP

#include "render/Shader.hpp"
#include "render/Texture.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <memory>

class ShaderProgram {
public:
    /**
     * Initializes a ShaderProgram.
     */
    ShaderProgram();

    /**
     * Initializes a ShaderProgram with the fragment and vertex shader provided.
     */
    ShaderProgram(const std::string& vertex_file, const std::string& fragment_file);

    /**
     * Attaches a shader to this program.
     * @param shader A shader.
     */
    void attach(const Shader& shader);

    /**
     * Links all the shaders into the program. Afterwards, no more shaders
     * can be attached.
     */
    void link();

    /**
     * Binds this ShaderProgram for OpenGL operations.
     */
    void use();

    /**
     * Returns the location of a uniform variable in the ShaderProgram. This uses
     * a cache to only lookup each locations
     * @param uniform The name of the uniform variable.
     * @return The uniform location (ID).
     */
    GLuint getUniformId(const std::string& uniform);

    /**
     * Sends a uniform integer value to the graphics card.
     * @param uniform The name of the uniform variable.
     * @param integer The value.
     */
    void send(const std::string& uniform, int integer);

    /**
     * Sends a uniform float value to the graphics card.
     * @param uniform The name of the uniform variable.
     * @param scalar The value.
     */
    void send(const std::string& uniform, float scalar);

    /**
     * Sends a uniform vector value to the graphics card.
     * @param uniform The name of the uniform variable.
     * @param vector The value.
     */
    void send(const std::string& uniform, glm::vec3 vector);

    /**
     * Sends a uniform vector value to the graphics card.
     * @param uniform The name of the uniform variable.
     * @param vector The value.
     */
    void send(const std::string& uniform, glm::vec4 vector);

    /**
     * Sends a uniform matrix value to the graphics card.
     * @param uniform The name of the uniform variable.
     * @param matrix The value.
     */
    void send(const std::string& uniform, glm::mat4 matrix);

    /**
     * Binds a texture into a sampler uniform in the shader.
     * @param uniform The name of the uniform variable.
     * @param texture The texture.
     * @param location The texture slot number.
     */
    void send(const std::string& uniform, std::shared_ptr<Texture> texture, int location = 0);

    /**
     * Returns the OpenGL handle of this shader program for direct access.
     * @return The OpenGL shader program id.
     */
    GLuint getHandle() const;

    /**
     * Returns the link log reported by the graphics card.
     * @return The link log.
     */
    std::string getLog() const;

private:
    GLuint mHandle;
    std::map<std::string, GLuint> mUniformCache;

};

#endif
