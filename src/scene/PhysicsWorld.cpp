#include "PhysicsWorld.hpp"

PhysicsWorld::PhysicsWorld() {
	mBroadphase = std::make_shared<btDbvtBroadphase>();
	mConfiguration = std::make_shared<btDefaultCollisionConfiguration>();
	mDispatcher = std::make_shared<btCollisionDispatcher>(mConfiguration.get());
	mSolver = std::make_shared<btSequentialImpulseConstraintSolver>();

	mDynamicsWorld = std::make_shared<btDiscreteDynamicsWorld>(mDispatcher.get(), mBroadphase.get(), mSolver.get(), mConfiguration.get());
}

void PhysicsWorld::setGravity(const glm::vec3& gravity) {
	mDynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
}

void PhysicsWorld::add(std::shared_ptr<PhysicsNode> node) {
	mNodes.push_back(node);
	mDynamicsWorld->addRigidBody(node->getRigidBody().get());
}

void PhysicsWorld::remove(std::shared_ptr<PhysicsNode> node) {
	mNodes.remove(node);
	mDynamicsWorld->removeRigidBody(node->getRigidBody().get());
}

void PhysicsWorld::stepSimulation(btScalar timestep, int maxSubSteps, btScalar fixedTimeStep) {
	mDynamicsWorld->stepSimulation(timestep, maxSubSteps, fixedTimeStep);
}



	