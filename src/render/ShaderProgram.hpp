#ifndef _RENDER_SHADERPROGRAM_HPP
#define _RENDER_SHADERPROGRAM_HPP

#include "render/Shader.hpp"

#include <GL/glew.h>
#include <string>

class ShaderProgram {
public:
    ShaderProgram();
    void attach(const Shader& shader);
    void link();

    GLuint getHandle() const;
    std::string getLog() const;

private:
    GLuint mHandle;

};

#endif
