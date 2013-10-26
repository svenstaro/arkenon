#ifndef _OBJECTS_SPACECRAFT_HPP
#define _OBJECTS_SPACECRAFT_HPP

#include <memory>

#include "scene/Node.hpp"
#include "scene/Mesh.hpp"
#include "scene/Velocity.hpp"

class Spacecraft : public Node {
public:
    Spacecraft(const std::string& name);

    void initialize();
    void onEvent(const Event* event);

private:
    std::shared_ptr<Mesh> mMesh;
    std::shared_ptr<Velocity> mVelocity;
};

#endif
