#include "ShaderProgram.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

ShaderProgram::ShaderProgram()
{
    mHandle = glCreateProgram();
}

void ShaderProgram::attach(const Shader &shader)
{
    glAttachShader(mHandle, shader.getHandle());
}

void ShaderProgram::link()
{
    glLinkProgram(mHandle);
    std::cout << "Linking Program: " << getLog() << std::endl;
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
    glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &log_length);
    std::vector<char> error_message(std::max(log_length, int(1)));
    glGetProgramInfoLog(mHandle, log_length, NULL, &error_message[0]);
    return std::string(error_message.begin(), error_message.end());
}
