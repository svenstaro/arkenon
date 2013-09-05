#ifndef _SCENE_PHYSICSWORLD_HPP
#define _SCENE_PHYSICSWORLD_HPP

#include "scene/PhysicsNode.hpp"
#include <list>

class PhysicsWorld  {
public:
    PhysicsWorld();

    void setGravity(const glm::vec3& gravity);

    void add(std::shared_ptr<PhysicsNode> node);
    void remove(std::shared_ptr<PhysicsNode> node);

    void stepSimulation(btScalar timestep, int maxSubSteps = 1, btScalar fixedTimeStep = btScalar(1.)/btScalar(60.));

private:
	std::shared_ptr<btBroadphaseInterface> mBroadphase;
	std::shared_ptr<btDefaultCollisionConfiguration> mConfiguration;
	std::shared_ptr<btCollisionDispatcher> mDispatcher;
	std::shared_ptr<btSequentialImpulseConstraintSolver> mSolver;

	std::shared_ptr<btDiscreteDynamicsWorld> mDynamicsWorld;

	std::list<std::shared_ptr<PhysicsNode>> mNodes;
};

#endif
