#include "utils.hpp"

#include <GL/glew.h>
#include <iostream>

bool glCheck(const char* file, int line) {
    int error = glGetError();
    if(error == GL_NO_ERROR) return true;

    std::cerr << "[[ " << file << ":" << line << " ]] " << std::endl;

    while(error != GL_NO_ERROR) {
        switch (error) {
            case GL_INVALID_ENUM:
                std::cerr << "GL_INVALID_ENUM: an unacceptable value has been specified for an enumerated argument" << std::endl;
                break;
            case GL_INVALID_VALUE:
                std::cerr << "GL_INVALID_VALUE: a numeric argument is out of range" << std::endl;
                break;
            case GL_INVALID_OPERATION:
                std::cerr << "GL_INVALID_OPERATION: the specified operation is not allowed in the current state" << std::endl;
                break;
            case GL_OUT_OF_MEMORY:
                std::cerr << "GL_OUT_OF_MEMORY: there is not enough memory left to execute the command" << std::endl;
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION_EXT: the object bound to FRAMEBUFFER_BINDING_EXT is not \"framebuffer complete\"" << std::endl;
                break;
            default:
                std::cerr << "Error not listed. Value: " << error << std::endl;
                break;
        }
        error = glGetError();
    }
    int* a = nullptr;
    *a = 1;
    return false;
}
