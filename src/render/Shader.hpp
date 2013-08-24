#ifndef _RENDER_SHADER_HPP
#define _RENDER_SHADER_HPP

#include <GL/glew.h>
#include <string>

class Shader {
public:
    enum Type {
        Fragment,   ///< A fragment shader.
        Vertex      ///< A vertex shader.
    };

public:
    /**
     * Initializes a shader.
     * @param type The type of shader.
     */
    Shader(const Type type);

    /**
     * Initializes, loads and compiles a shader.
     * @param type The type of shader.
     * @param file The path to the source file.
     */
    Shader(const Type type, const std::string& file);

    /**
     * Loads the shader source file.
     * @param file The path to the source file.
     */
    void load(const std::string& file);

    /**
     * Compiles the shader on the graphics card.
     */
    void compile();

    /**
     * Returns the OpenGL handle of this shader for direct access.
     * @return The OpenGL shader id.
     */
    GLuint getHandle() const;

    /**
     * Returns the compilation log reported by the graphics card.
     * @return The compilation log.
     */
    std::string getLog() const;

private:
    const Type mType;
    std::string mCode;
    GLuint mHandle;

};

#endif
