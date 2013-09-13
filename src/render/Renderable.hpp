#ifndef _RENDER_RENDERABLE_HPP
#define _RENDER_RENDERABLE_HPP

#include "render/Material.hpp"
#include <memory>

class Renderable {
public:
    virtual ~Renderable() = 0;

    virtual std::shared_ptr<Material> getMaterial();
    virtual glm::mat4 getModelMatrix() const = 0;
    virtual void draw() = 0;
};

#endif
