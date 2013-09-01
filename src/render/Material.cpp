#include "Material.hpp"

#include <iostream>

Material::Material()
    : mDiffuseColor(1, 1, 1, 1)
{}

void Material::setDiffuseColor(const glm::vec4& color)
{
    mDiffuseColor = color;
}

void Material::setNormalTexture(std::shared_ptr<Texture> texture) {
    mNormalTexture = texture;
}

void Material::setDiffuseTexture(std::shared_ptr<Texture> texture) {
    mDiffuseTexture = texture;
}

void Material::setSpecularTexture(std::shared_ptr<Texture> texture) {
    mSpecularTexture = texture;
}

const glm::vec4&Material::getDiffuseColor()
{
    return mDiffuseColor;
}

std::shared_ptr<Texture> Material::getNormalTexture() {
    return mNormalTexture;
}

std::shared_ptr<Texture> Material::getDiffuseTexture() {
    return mDiffuseTexture;
}

std::shared_ptr<Texture> Material::getSpecularTexture() {
    return mSpecularTexture;
}
