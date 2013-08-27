#include "Camera.hpp"

Camera::Camera(const std::string& name, Type type, const glm::vec2& viewport_size, float field_of_view, float near_clip, float far_clip)
    : Node(name),
      mType(type),
      mViewportSize(viewport_size),
      mFieldOfView(field_of_view),
      mNearClip(near_clip),
      mFarClip(far_clip)
{}

glm::mat4 Camera::getViewProjectionMatrix() const
{
    return getProjectionMatrix() * getViewMatrix();
}

glm::mat4 Camera::getViewMatrix() const
{
    //if(getParent()) return glm::inverse(getTransformationMatrix()) * getParent()->getTransformationMatrix();
    return glm::inverse(getAbsoluteTransformationMatrix());
}

glm::mat4 Camera::getProjectionMatrix() const
{
    if(mType == Perspective)
    {
        return glm::perspective(mFieldOfView, mViewportSize.x / mViewportSize.y, mNearClip, mFarClip);
    }
    else
    {
        glm::vec2 s = mViewportSize / 2.f * mFieldOfView; // field of view = zoom factor

        if(mType == Orthographic)
            return glm::ortho(-s.x, s.x, -s.y, s.y, mNearClip, mFarClip);
        else if(mType == Screen)
            return glm::ortho(-s.x, s.x, s.y, -s.y, mNearClip, mFarClip);
        else
            return glm::mat4(1.f);
    }
}

void Camera::setType(Camera::Type type)
{
    mType = type;
}

void Camera::setViewportSize(const glm::vec2& viewport_size)
{
    mViewportSize = viewport_size;
}

void Camera::setFieldOfView(float field_of_view)
{
    if(mType != Perspective)
        std::cout << "Warning: setting field of view on non-perspective camera '" << getName() << "' has no effect." << std::endl;

    mFieldOfView = field_of_view;
}

void Camera::setClipping(float near_clip, float far_clip)
{
    if(mType != Perspective)
        std::cout << "Warning: setting clipping on non-perspective camera '" << getName() << "' has no effect." << std::endl;

    mNearClip = near_clip;
    mFarClip = far_clip;
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
