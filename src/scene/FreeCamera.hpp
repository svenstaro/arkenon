#ifndef _SCENE_FREECAMERA_HPP
#define _SCENE_FREECAMERA_HPP

#include "scene/Node.hpp"
#include "window/Window.hpp"

class FreeCamera : public Node {
public:
    FreeCamera(const std::string& name, const Window& window);

    void onUpdate(double dt);

private:
    const Window& mWindow;

    glm::vec2 mPreviousMousePosition;
    glm::vec3 mSpeed;
    glm::vec2 mMouseDiff;
};

#endif
