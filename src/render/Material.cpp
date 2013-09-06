#include "Material.hpp"

#include <iostream>

Material::Material()
    : mDiffuseColor(1, 1, 1, 1),
      mSpecularShininess(20),
      mSpecularColorMix(1)
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

void Material::setSpecularShininess(float value) {
    mSpecularShininess = value;
}

void Material::setSpecularColorMix(float value) {
    mSpecularColorMix = value;
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

float Material::getSpecularShininess() const {
    return mSpecularShininess;
}

float Material::getSpecularColorMix() const {
    return mSpecularColorMix;
}
