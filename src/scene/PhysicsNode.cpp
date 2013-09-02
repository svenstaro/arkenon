#include "PhysicsNode.hpp"

PhysicsNode::PhysicsNode(const std::string& name, const glm::vec3& initpos, std::shared_ptr<btCollisionShape> shape, btScalar mass) 
	: Node(name)
{
	mMass = mass;
	mShape = shape;
	mMotionState = std::make_shared<PhysicsNodeMotionState>(
		btTransform(
			btQuaternion(0,0,0,1),
			btVector3(initpos.x, initpos.y, initpos.z)
		)

	);

	mShape->calculateLocalInertia(mMass, mInertia);

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mMass, mMotionState.get(), shape.get(), mInertia);
    mRigidBody = std::make_shared<btRigidBody>(rigidBodyCI);
}

btScalar PhysicsNode::getMass() {
	return mMass;
}
btVector3 PhysicsNode::getInertia() {
	return mInertia;
}

std::shared_ptr<btRigidBody> PhysicsNode::getRigidBody() {
	return mRigidBody;
}


