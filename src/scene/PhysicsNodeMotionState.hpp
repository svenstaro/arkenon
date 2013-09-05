#ifndef _SCENE_PHYSICSNODEMOTIONSTATE_HPP
#define _SCENE_PHYSICSNODEMOTIONSTATE_HPP

#include "scene/PhysicsNode.hpp"

class PhysicsNode;

class PhysicsNodeMotionState : public btMotionState {
public:
	PhysicsNodeMotionState(const btTransform &initialpos);

    PhysicsNodeMotionState(const btTransform &initialpos, std::shared_ptr<PhysicsNode> node);

    void setNode(std::shared_ptr<PhysicsNode> node);

    void getWorldTransform(btTransform &worldTrans) const;

    void setWorldTransform(const btTransform &worldTrans) override;
    
private:
    std::shared_ptr<PhysicsNode> mNode;
    btTransform mInitPos;
};

#endif