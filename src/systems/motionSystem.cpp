#include "systems/motionSystem.h"

void MotionSystem::update(
    std::unordered_map<unsigned int, TransformComponent> &transformComponents,
    std::unordered_map<unsigned int, PhysicsComponent> &physicsComponents,
    float dt) {

  // Assume all entities with a physics component also have a transform
  for (std::pair<unsigned int, PhysicsComponent> entity : physicsComponents) {
    transformComponents[entity.first].position += entity.second.velocity * dt;
    transformComponents[entity.first].eulers +=
        entity.second.eulerVelocity * dt;
    // Keep eulers in range [0, 360]
    if (transformComponents[entity.first].eulers.z > 360) {
      transformComponents[entity.first].eulers.z -= 360;
    }
  }
}