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

    void setDiffuseColor(const glm::vec4& color);
    void setNormalTexture(std::shared_ptr<Texture> texture);
    void setDiffuseTexture(std::shared_ptr<Texture> texture);
    void setSpecularTexture(std::shared_ptr<Texture> texture);

    const glm::vec4& getDiffuseColor();
    std::shared_ptr<Texture> getNormalTexture();
    std::shared_ptr<Texture> getDiffuseTexture();
    std::shared_ptr<Texture> getSpecularTexture();


private:
    glm::vec4 mDiffuseColor;
    std::shared_ptr<Texture> mDiffuseTexture;
    std::shared_ptr<Texture> mNormalTexture;
    std::shared_ptr<Texture> mSpecularTexture;
};

#endif
