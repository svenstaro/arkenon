#ifndef _SCENE_PHYSICSNODE_HPP
#define _SCENE_PHYSICSNODE_HPP

#include <bullet/btBulletDynamicsCommon.h>

#include "scene/Node.hpp"
#include "scene/PhysicsNodeMotionState.hpp"

class PhysicsNodeMotionState;

//Dynamic
class PhysicsNode : public Node {
public:
    PhysicsNode(const std::string& name, const glm::vec3& initpos, std::shared_ptr<btCollisionShape> shape, btScalar mass);

    btScalar getMass();
    btVector3 getInertia();

    std::shared_ptr<btRigidBody> getRigidBody();

private:
	btScalar mMass;
	btVector3 mInertia;
	std::shared_ptr<btCollisionShape> mShape;
	std::shared_ptr<PhysicsNodeMotionState> mMotionState;
	std::shared_ptr<btRigidBody> mRigidBody;
};

#endif
