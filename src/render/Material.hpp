#ifndef _RENDER_MATERIAL_HPP
#define _RENDER_MATERIAL_HPP

#include "render/Texture.hpp"
#include <memory>

class Material {
public:
    /**
     * Initializes a Material.
     */
    Material();

    void setNormalTexture(std::shared_ptr<Texture> texture);

    void setDiffuseTexture(std::shared_ptr<Texture> texture);

    void setSpecularTexture(std::shared_ptr<Texture> texture);

    std::shared_ptr<Texture> getNormalTexture();

    std::shared_ptr<Texture> getDiffuseTexture();

    std::shared_ptr<Texture> getSpecularTexture();


private:
    std::shared_ptr<Texture> mDiffuse;
    std::shared_ptr<Texture> mNormal;
    std::shared_ptr<Texture> mSpecular;
};

#endif
