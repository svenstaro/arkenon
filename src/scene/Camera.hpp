#ifndef _SCENE_CAMERA_HPP
#define _SCENE_CAMERA_HPP

#include "scene/Node.hpp"

#include <glm/glm.hpp>

#include <memory>

class Camera : public Node {
public:
    Camera(const std::string& name,
           float field_of_view = 60.f,
           float aspect_ratio = 1.f,
           float near_clip = 0.1f,
           float far_clip = 100.f);

    glm::mat4 getViewProjectionMatrix();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void lookAt(const glm::vec3& target, bool absolute = true, const glm::vec3& up_direction = glm::vec3(0, 1, 0));

private:
    float mFieldOfView;
    float mAspectRatio;
    float mNearClip;
    float mFarClip;

};

#endif
