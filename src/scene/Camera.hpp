#ifndef _SCENE_CAMERA_HPP
#define _SCENE_CAMERA_HPP

#include "scene/Node.hpp"

#include <glm/glm.hpp>

#include <memory>

class Camera : public Node {
public:
    enum Type {
        Perspective,
        Orthographic
    };

public:
    /**
     * Initializes a camera.
     * @param name The node name.
     * @param type Perspective or orthographic mode.
     * @param viewport_size The size of the viewport the camera renders to.
     * @param field_of_view The FOV in degrees for perspective cameras, the zoom level for orthographic cameras.
     * @param near_clip The near clip distance (not affected by the zoom).
     * @param far_clip The far clip distance (not affected by the zoom).
     */
    Camera(const std::string& name,
           Type type,
           const glm::vec2& viewport_size,
           float field_of_view,
           float near_clip = 0.1f,
           float far_clip = 100.f);

    glm::mat4 getViewProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void setType(Type type);
    void setViewportSize(const glm::vec2& viewport_size);

    /**
     * @brief Sets the FOV on perspective cameras, or the zoom factor on orthographic cameras.
     * @param field_of_view The new FOV in degrees, or the zoom factor.
     */
    void setFieldOfView(float field_of_view);
    void setClipping(float near_clip, float far_clip);

    void lookAt(const glm::vec3& target, bool absolute = true, const glm::vec3& up_direction = glm::vec3(0, 1, 0));

private:
    Type mType;
    glm::vec2 mViewportSize;
    float mFieldOfView;
    float mNearClip;
    float mFarClip;

};

#endif
