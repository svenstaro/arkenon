#include "Spacecraft.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Spacecraft::Spacecraft(const std::string& name)
    : Node(name)
{}

void Spacecraft::initialize()
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile("data/models/fighter.dae", aiProcessPreset_TargetRealtime_Fast);

    mMesh = std::make_shared<Mesh>("spacecraft-mesh");
    mMesh->load(scene->mMeshes[0]);
    mMesh->commit();
    mMesh->rotation = glm::quat(glm::vec3(-M_PI/2, 0, 0));
    mMesh->position = glm::vec3(0, 5, 0);
    std::shared_ptr<Material> material = std::make_shared<Material>();
    material->setDiffuseTexture(std::make_shared<Texture>("data/textures/fighter.png"));
    material->setSpecularShininess(10);
    material->setDiffuseColor(glm::vec4(0.5, 0.5, 0.5, 1.0));
    mMesh->setMaterial(material);
    addChild(mMesh);

    mVelocity = std::make_shared<Velocity>("spacecraft-velocity");
    mVelocity->linearVelocity = glm::vec3(0, 0, 2);
    mVelocity->angularVelocity = glm::vec3(0, 0.5, 0);
    mVelocity->useLocalRotation = true;
    mVelocity->linearDamping = 1.f;
    addChild(mVelocity);
}

void Spacecraft::onEvent(const Event* event)
{
    if(event->type == Event::MousePress) {
        if( ((MousePressEvent*)event)->button == GLFW_MOUSE_BUTTON_LEFT ) {
            mVelocity->linearVelocity += glm::vec3(0, 0, 5);
        }
    }
}
