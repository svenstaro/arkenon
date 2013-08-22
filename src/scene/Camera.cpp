#include "Camera.hpp"

Camera::Camera(const std::string& name, float field_of_view, float aspect_ratio, float near_clip, float far_clip)
    : Node(name),
      mFieldOfView(field_of_view),
      mAspectRatio(aspect_ratio),
      mNearClip(near_clip),
      mFarClip(far_clip)
{}

glm::mat4 Camera::getViewProjectionMatrix()
{
    return getProjectionMatrix() * getViewMatrix();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::inverse(getAbsoluteTransformationMatrix());
}

glm::mat4 Camera::getProjectionMatrix()
{
    return glm::perspective(mFieldOfView, mAspectRatio, mNearClip, mFarClip);
}

void Camera::lookAt(const glm::vec3& target, bool absolute, const glm::vec3& up_direction) {
    glm::vec3 pos = absolute ? getAbsolutePosition() : position;

    glm::vec3 forward = target - pos;
    glm::vec3 up = up_direction;
    forward = glm::orthonormalize(forward, up);
    glm::vec3 right = glm::cross(up, forward);

    glm::quat ret;
    ret.w = sqrtf(1.0f + right.x + up.y + forward.z) * 0.5f;
    float w4_recip = 1.0f / (4.0f * ret.w);
    ret.x = (up.z - forward.y) * w4_recip;
    ret.y = (forward.x - right.z) * w4_recip;
    ret.z = (right.y - up.x) * w4_recip;

    rotation = ret;
}
