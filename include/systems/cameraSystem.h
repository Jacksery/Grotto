#pragma once
#include "components/cameraComponent.h"
#include "components/transformComponent.h"
#include "config/config.h"

class CameraSystem {
public:
  CameraSystem(unsigned int shader, GLFWwindow *window);

  bool update(
      std::unordered_map<unsigned int, TransformComponent> &transformComponents,
      unsigned int cameraID, CameraComponent &cameraComponent, float dt);

private:
  unsigned int viewLocation;
  glm::vec3 globalUp = {0.0f, 0.0f, 1.0f};
  GLFWwindow *window;
};