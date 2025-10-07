#pragma once
#include "config/config.h"

#include "components/cameraComponent.h"
#include "components/physicsComponent.h"
#include "components/renderComponent.h"
#include "components/transformComponent.h"

#include "systems/cameraSystem.h"
#include "systems/motionSystem.h"
#include "systems/renderSystem.h"

#include "view/shader.h"

class App {
public:
  App();
  ~App();

  void run();

  unsigned int makeEntity();
  unsigned int makeCubeMesh(glm::vec3 size);
  unsigned int makeTexture(const char *path);

  void initOpenGL();
  void initSystems();

  // Window / input helpers
  void handleResize(int width, int height);
  void setActive(bool active);

  // Components
  std::unordered_map<unsigned int, TransformComponent> transformComponents;
  std::unordered_map<unsigned int, PhysicsComponent> physicsComponents;
  CameraComponent *cameraComponent;
  unsigned int cameraID;
  std::unordered_map<unsigned int, RenderComponent> renderComponents;

private:
  void initGLFW();

  unsigned int entityCount = 0;
  GLFWwindow *window;

  std::vector<unsigned int> VAOs;
  std::vector<unsigned int> VBOs;
  std::vector<unsigned int> textures;

  unsigned int shader;

  // Systems
  MotionSystem *motionSystem;
  CameraSystem *cameraSystem;
  RenderSystem *renderSystem;
  // runtime state
  bool isActive = true;
};