#ifndef _RENDER_SHADER_HPP
#define _RENDER_SHADER_HPP

#include <GL/glew.h>
#include <string>

class Shader {
public:
    enum Type {
        Fragment,
        Vertex
    };

public:
    Shader(const Type type);
    Shader(const Type type, const std::string& file);
    void load(const std::string& file);
    void compile();

    GLuint getHandle() const;
    std::string getLog() const;

private:
    const Type mType;
    std::string mCode;
    GLuint mHandle;

};

#endif
