#include "Renderable.hpp"

Renderable::~Renderable()
{}

std::shared_ptr<Material> Renderable::getMaterial()
{
    return nullptr;
}
