#include "config/config.h"
#include "controller/app.h"

#include "components/cameraComponent.h"
#include "components/physicsComponent.h"
#include "components/renderComponent.h"
#include "components/transformComponent.h"
#include "logging/logging.h"

int main() {

  App *app = new App();

  TransformComponent transform;
  PhysicsComponent physics;
  RenderComponent render;
  CameraComponent *camera = new CameraComponent();

  unsigned int cubeEntity = app->makeEntity(); // Returns id of new entity
  Logging::Info("APP",
                "Created cube entity with ID: " + std::to_string(cubeEntity));

  transform.position = {3.0f, 0.0f, 0.25f};
  transform.eulers = {0.0f, 0.0f, 0.0f};
  physics.velocity = {0.0f, 0.0f, 0.0f};
  physics.eulerVelocity = {0.0f, 0.0f, 10.0f};
  render.mesh = app->makeCubeMesh({0.25f, 0.25f, 0.25f});
  render.material = app->makeTexture("../../../res/textures/brick.jpg");
  if (render.material == 0) {
    Logging::Error("APP", "Failed to create texture, ensure the path is valid");
    delete app;
    return -1;
  }

  app->transformComponents[cubeEntity] = transform;
  app->physicsComponents[cubeEntity] = physics;
  app->renderComponents[cubeEntity] = render;

  unsigned int cameraEntity = app->makeEntity();
  Logging::Info("APP", "Created camera entity with ID: " +
                           std::to_string(cameraEntity));
  transform.position = {0.0f, 0.0f, 1.0f};
  transform.eulers = {0.0f, 0.0f, 0.0f};

  app->transformComponents[cameraEntity] = transform;
  app->cameraComponent = camera;
  app->cameraID = cameraEntity;

  // Setup shaders and projection matrix
  app->initOpenGL();

  // Instantiate systems for managing game state
  app->initSystems();

  app->run();

  delete app;
  return 0;
}