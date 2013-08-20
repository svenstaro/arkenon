#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Shader::Shader(const Type type)
    : mType(type)
{
    if(mType == Fragment) {
        mHandle = glCreateShader(GL_FRAGMENT_SHADER);
    } else if(mType == Vertex) {
        mHandle = glCreateShader(GL_VERTEX_SHADER);
    } else {
        std::cerr << "Unknown shader type: " << mType << std::endl;
    }
}

Shader::Shader(const Shader::Type type, const std::string &file)
    : Shader(type)
{
    load(file);
    compile();
}

void Shader::load(const std::string &file)
{
    std::ifstream stream(file);
    std::stringstream buffer;
    buffer << stream.rdbuf();
    mCode = buffer.str();
}

void Shader::compile()
{
    std::cout << mCode << std::endl;
    const char* source = mCode.c_str();
    glShaderSource(mHandle, 1, &source, NULL);
    glCompileShader(mHandle);

    // Check Shader
    std::cout << "Compiled shader: " << getLog() << std::endl;
}

std::string Shader::getLog() const
{
    GLint result = GL_FALSE;
    int log_length;
    glGetShaderiv(mHandle, GL_COMPILE_STATUS, &result);
    glGetShaderiv(mHandle, GL_INFO_LOG_LENGTH, &log_length);
    std::vector<char> error_message(log_length);
    glGetShaderInfoLog(mHandle, log_length, NULL, &error_message[0]);
    return std::string(error_message.begin(), error_message.end());
}


GLuint Shader::getHandle() const
{
    return mHandle;
}
