#ifndef _RENDER_RENDERABLE_HPP
#define _RENDER_RENDERABLE_HPP

#include "scene/Camera.hpp"
#include "render/ShaderProgram.hpp"

#include <memory>

class Renderable {
public:
    virtual ~Renderable() = 0;
    virtual void render(std::shared_ptr<Camera> camera, std::shared_ptr<ShaderProgram> shader_program) = 0;
};

#endif
