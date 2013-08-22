#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "window/GameWindow.hpp"
#include "render/Shader.hpp"
#include "render/ShaderProgram.hpp"
#include "render/VertexBuffer.hpp"
#include "render/ForwardRenderer.hpp"
#include "scene/Mesh.hpp"
#include "scene/Camera.hpp"

// TESTING INCLUDES
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

int main()
{
    GameWindow window;
    //window.setSize(1024, 600);

    ForwardRenderer renderer;

    Node root("root");
    Mesh* mesh = (Mesh*) root.addChild(new Mesh("mesh"));

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile("data/models/test.dae", aiProcessPreset_TargetRealtime_Fast);
    mesh->load(scene->mMeshes[0]);
    mesh->commit();

    Camera* camera = (Camera*) root.addChild(new Camera("camera", 60, window.getAspectRatio(), 0.1f, 100.f));
    camera->position = glm::vec3(0, 0, 3); // camera looks at -z

    double time = 0;
    while(window.isOpen()) {
        window.update();

        time = time + window.getFrameDuration();
        mesh->rotation = glm::quat(glm::vec3(0, window.getFrameDuration() * 0.3, 0)) * mesh->rotation;

        window.setBackgroundColor(glm::vec4(0.2, 0.3, 0.5, 1.f));
        window.clear();

        renderer.prepare();
        renderer.registerMesh(mesh);
        renderer.setCamera(camera);
        renderer.render();
        renderer.cleanup();

        window.display();
    }

    return 0;
}
