#include "RenderTarget.hpp"

RenderTarget::RenderTarget(glm::vec2 size)
    : mSize(size)
{}

RenderTarget::~RenderTarget()
{}

const glm::vec2&RenderTarget::getSize() const
{
    return mSize;
}
