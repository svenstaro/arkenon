#include "Velocity.hpp"

Velocity::Velocity(const std::string& name)
    : Node(name)
{}

void Velocity::onUpdate(double dt)
{
    // apply damping
    linearVelocity *= std::max(0.f, 1 - linearDamping * (float)dt);
    angularVelocity *= std::max(0.f, 1 - angularDamping * (float)dt);

    // apply rotation
    Node* target = getParent();
    target->position += (useLocalRotation ? target->rotation * linearVelocity : linearVelocity) * (float)dt;

    glm::vec3 euler = angularVelocity * (float)dt;
    target->rotation = target->rotation * glm::toQuat(glm::eulerAngleYXZ(euler.y, euler.x, euler.z));
}
