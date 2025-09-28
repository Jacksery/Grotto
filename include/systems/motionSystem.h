#pragma once
#include "components/physicsComponent.h"
#include "components/transformComponent.h"
#include "config/config.h"

class MotionSystem {
public:
  void update(
      std::unordered_map<unsigned int, TransformComponent> &transformComponents,
      std::unordered_map<unsigned int, PhysicsComponent> &physicsComponents,
      float dt);
};