#include "Material.hpp"

Material::Material() {

}

void Material::setNormalTexture(std::shared_ptr<Texture> texture) {
	mNormal = texture;
}

void Material::setDiffuseTexture(std::shared_ptr<Texture> texture) {
	mDiffuse = texture;
}

void Material::setSpecularTexture(std::shared_ptr<Texture> texture) {
	mSpecular = texture;
}

std::shared_ptr<Texture> Material::getNormalTexture() {
	return mNormal;
}

std::shared_ptr<Texture> Material::getDiffuseTexture() {
	return mDiffuse;
}

std::shared_ptr<Texture> Material::getSpecularTexture() {
	return mSpecular;
}