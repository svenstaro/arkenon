#ifndef _SCENE_SHAPE2D_HPP
#define _SCENE_SHAPE2D_HPP

#include <memory>

#include <assimp/mesh.h>

#include "render/VertexBuffer.hpp"
#include "render/Vertex.hpp"
#include "render/ShaderProgram.hpp"
#include "render/Texture.hpp"
#include "render/Renderable.hpp"
#include "scene/Node.hpp"
#include "scene/Camera.hpp"
#include "Rect.hpp"

class Shape2D : public Node, public Renderable {
public:
    Shape2D(const std::string& name);

    /**
     * Creates a rectangular shape.
     * @param size
     * @param subrect The subrect of the texture to use, in pixel size.
     * @param split9_factor For values < 1, this creates a 9-patch (see Android documentation) shape
     *                      within the selected subrect. The inner part of the 9-patch is
     *                      ```subrect.size * split9_factor``` in size, centered within the border.
     * @param texture_size If no texture has been set previously, this is required.
     */
    void makeRectangle(const glm::vec2& size,
                       const Rect& subrect,
                       float split9_factor = 1.f,
                       const glm::vec2& texture_size = glm::vec2(0, 0));

    void setTexture(std::shared_ptr<Texture> texture);

    void render(std::shared_ptr<Camera> camera, std::shared_ptr<ShaderProgram> shader_program);

private:
    VertexBuffer mVertexBuffer;
    std::shared_ptr<Texture> mTexture;

};

#endif
