#pragma once
#include "components/renderComponent.h"
#include "components/transformComponent.h"
#include "config/config.h"

class RenderSystem {
public:
  RenderSystem(unsigned int shader, GLFWwindow *window);

  void update(
      std::unordered_map<unsigned int, TransformComponent> &transformComponents,
      std::unordered_map<unsigned int, RenderComponent> &renderComponents);

private:
  unsigned int modelLocation;
  GLFWwindow *window;
};