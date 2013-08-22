#ifndef _RENDER_SHADERPROGRAM_HPP
#define _RENDER_SHADERPROGRAM_HPP

#include "render/Shader.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <map>

class ShaderProgram {
public:
    ShaderProgram();
    void attach(const Shader& shader);
    void link();
    void use();

    GLuint getUniformId(const std::string& uniform);
    void send(const std::string& uniform, float scalar);
    void send(const std::string& uniform, glm::vec4 vector);
    void send(const std::string& uniform, glm::mat4 matrix);

    GLuint getHandle() const;
    std::string getLog() const;

private:
    GLuint mHandle;
    std::map<std::string, GLuint> mUniformCache;

};

#endif
