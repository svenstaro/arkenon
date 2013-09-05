
#include "PhysicsNodeMotionState.hpp"


PhysicsNodeMotionState::PhysicsNodeMotionState(const btTransform &initialpos) {
	mInitPos = initialpos;
}


PhysicsNodeMotionState::PhysicsNodeMotionState(const btTransform &initialpos, std::shared_ptr<PhysicsNode> node) {
	mInitPos = initialpos;
	mNode = node;
}

void PhysicsNodeMotionState::setNode(std::shared_ptr<PhysicsNode> node) {
	mNode = node;
}

void PhysicsNodeMotionState::getWorldTransform(btTransform &worldTrans) const {
	worldTrans = mInitPos;
}

void PhysicsNodeMotionState::setWorldTransform(const btTransform &worldTrans) {
	if(mNode) {
		btQuaternion rot = worldTrans.getRotation();
		mNode->setAbsoluteRotation(glm::quat((float)rot.getW(), (float)rot.getX(), (float)rot.getY(), (float)rot.getZ()));

		btVector3 pos = worldTrans.getOrigin();
		mNode->setAbsolutePosition(glm::vec3((float)pos.getX(), (float)pos.getY(), (float)pos.getZ()));
	}
}
    
