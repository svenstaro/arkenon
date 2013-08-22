#include "Shader.hpp"
#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Shader::Shader(const Type type)
    : mType(type)
{
    if(mType == Fragment) {
        mHandle = glCreateShader(GL_FRAGMENT_SHADER);
        GL_CHECK();
    } else if(mType == Vertex) {
        mHandle = glCreateShader(GL_VERTEX_SHADER);
        GL_CHECK();
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
    const char* source = mCode.c_str();
    glShaderSource(mHandle, 1, &source, NULL);
    GL_CHECK();
    glCompileShader(mHandle);
    GL_CHECK();

    // Check Shader
    const std::string& log = getLog();
    if(log.length() > 0) {
        std::cerr << "Shader Compilation Error: " << std::endl << log << std::endl;
    }
}

std::string Shader::getLog() const
{
    GLint result = GL_FALSE;
    int log_length;
    glGetShaderiv(mHandle, GL_COMPILE_STATUS, &result);
    GL_CHECK();
    if(result == GL_TRUE) return "";
    glGetShaderiv(mHandle, GL_INFO_LOG_LENGTH, &log_length);
    GL_CHECK();
    std::vector<char> error_message(log_length);
    glGetShaderInfoLog(mHandle, log_length, NULL, &error_message[0]);
    GL_CHECK();
    return std::string(error_message.begin(), error_message.end());
}


GLuint Shader::getHandle() const
{
    return mHandle;
}
