#include "ShaderProgram.hpp"
#include "util/check.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

ShaderProgram::ShaderProgram()
{
    mHandle = glCreateProgram();
    GL_CHECK();
}

void ShaderProgram::attach(const Shader &shader)
{
    glAttachShader(mHandle, shader.getHandle());
    GL_CHECK();
}

void ShaderProgram::link()
{
    glLinkProgram(mHandle);
    GL_CHECK();

    const std::string& log = getLog();
    if(log.length() > 0) {
        std::cerr << "Shader Program Linking Error: " << std::endl << log << std::endl;
    }
}

void ShaderProgram::use()
{
    glUseProgram(mHandle);
    GL_CHECK();
}

GLuint ShaderProgram::getUniformId(const std::string& uniform)
{
    auto iter = mUniformCache.find(uniform);
    if(iter == mUniformCache.end())
    {
        GLuint id = glGetUniformLocation(mHandle, uniform.c_str());
        GL_CHECK();
        mUniformCache[uniform] = id;
        return id;
    }
    else
    {
        return iter->second;
    }
}

void ShaderProgram::send(const std::string& uniform, int integer)
{
    glUniform1iv(getUniformId(uniform), 1, &integer);
    GL_CHECK();
}

void ShaderProgram::send(const std::string& uniform, float scalar)
{
    glUniform1fv(getUniformId(uniform), 1, &scalar);
    GL_CHECK();
}

void ShaderProgram::send(const std::string& uniform, glm::vec3 vector)
{
    glUniform3fv(getUniformId(uniform), 1, &vector[0]);
    GL_CHECK();
}

void ShaderProgram::send(const std::string& uniform, glm::vec4 vector)
{
    glUniform4fv(getUniformId(uniform), 1, &vector[0]);
    GL_CHECK();
}

void ShaderProgram::send(const std::string& uniform, glm::mat4 matrix)
{
    glUniformMatrix4fv(getUniformId(uniform), 1, GL_FALSE, &matrix[0][0]);
    GL_CHECK();
}

void ShaderProgram::send(const std::string& uniform, std::shared_ptr<Texture> texture, int location)
{
    send(uniform, location); //(int)texture->getHandle());

    // select texture image unit
    glActiveTexture(GL_TEXTURE0 + location);
    GL_CHECK();

    // bind texture to texture image unit
    texture->bind();
}

GLuint ShaderProgram::getHandle() const
{
    return mHandle;
}

std::string ShaderProgram::getLog() const
{
    GLint result = GL_FALSE;
    int log_length;

    glGetProgramiv(mHandle, GL_LINK_STATUS, &result);
    GL_CHECK();
    if(result == GL_TRUE) return "";
    glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &log_length);
    GL_CHECK();
    std::vector<char> error_message(std::max(log_length, int(1)));
    glGetProgramInfoLog(mHandle, log_length, NULL, &error_message[0]);
    GL_CHECK();
    return std::string(error_message.begin(), error_message.end());
}
