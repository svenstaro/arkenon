#include "FreeCamera.hpp"

FreeCamera::FreeCamera(const std::string& name, const Window& window)
    : Node(name),
      mWindow(window)
{}

void FreeCamera::onUpdate(double dt)
{
    // apply rotation damping
    float factor = std::min(1.f, 30.f * (float)dt);
    mMouseDiff *= 1 - factor;

    // move speed damping
    factor = std::min(1.f, 12.f * float(dt));
    mSpeed *= 1 - factor;

    // get mouse difference
    glm::vec2 pos = mWindow.getMousePosition();
    glm::vec2 mouse_diff = (pos - mPreviousMousePosition);
    mPreviousMousePosition = pos;

    // apply sensitivity, add to accumulator
    mMouseDiff += mouse_diff * 0.5f;

    // get key presses
    glm::vec3 move(0, 0, 0);
    if(mWindow.isKeyDown(GLFW_KEY_W)) move.z--;
    if(mWindow.isKeyDown(GLFW_KEY_S)) move.z++;
    if(mWindow.isKeyDown(GLFW_KEY_D)) move.x++;
    if(mWindow.isKeyDown(GLFW_KEY_A)) move.x--;
    if(mWindow.isKeyDown(GLFW_KEY_E)) move.y++;
    if(mWindow.isKeyDown(GLFW_KEY_Q)) move.y--;
    if(mWindow.isKeyDown(GLFW_KEY_LEFT_SHIFT)) move *= 3;

    // apply key presses to speed
    if(move.x != 0) mSpeed.x = move.x;
    if(move.y != 0) mSpeed.y = move.y;
    if(move.z != 0) mSpeed.z = move.z;

    // calculate direction from rotation and local speed, apply to position
    glm::vec4 move_diff = glm::mat4_cast(rotation) * glm::vec4(mSpeed, 0);
    position += glm::vec3(move_diff.x, move_diff.y, move_diff.z) * (float)dt * 10.f;

    // apply rotation
    glm::vec2 rotation_diff = mMouseDiff * factor;
    rotation = glm::angleAxis(-rotation_diff.x, glm::vec3(0, 1, 0)) * rotation * glm::angleAxis(-rotation_diff.y, glm::vec3(1, 0, 0));
}
