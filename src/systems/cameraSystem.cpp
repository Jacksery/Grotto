#include "systems/cameraSystem.h"

CameraSystem::CameraSystem(unsigned int shader, GLFWwindow *window) {
  this->window = window;

  glUseProgram(shader);
  viewLocation = glGetUniformLocation(shader, "view");
}

bool CameraSystem::update(
    std::unordered_map<unsigned int, TransformComponent> &transformComponents,
    unsigned int cameraID, CameraComponent &cameraComponent, float dt) {

  glm::vec3 &pos = transformComponents[cameraID].position;
  glm::vec3 &eulers = transformComponents[cameraID].eulers;
  float theta = glm::radians(eulers.z);
  float phi = glm::radians(eulers.y);

  glm::vec3 &right = cameraComponent.right;
  glm::vec3 &up = cameraComponent.up;
  glm::vec3 &forwards = cameraComponent.forwards;

  forwards = {glm::cos(theta) * glm::cos(phi), glm::sin(theta) * glm::cos(phi),
              glm::sin(phi)};
  right = glm::normalize(glm::cross(forwards, globalUp));
  up = glm::normalize(glm::cross(right, forwards));

  glm::mat4 view = glm::lookAt(pos, pos + forwards, up);

  glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

  // Keys
  glm::vec3 dPos = {0.0f, 0.0f, 0.0f};
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    dPos.x += 1.0f;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    dPos.y -= 1.0f;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    dPos.x -= 1.0f;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    dPos.y += 1.0f;
  }
  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    dPos.z -= 1.0f;
  }
  if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
    dPos.z += 1.0f;
  }
  // Normalise movement to avoid faster diagonal movement
  if (glm::length(dPos) > 0.1f) {
    dPos = glm::normalize(dPos);
    pos += 0.05f * dPos.x * forwards;
    pos += 0.05f * dPos.y * right;
    pos += 0.05f * dPos.z * globalUp;
  }

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    return true;
  }

  // Mouse - use delta-based input without polling or recentering
  static bool shiftPressed = false;
  static bool cursorCaptured = true;
  static double lastX = 0.0, lastY = 0.0;
  static bool lastInit = false;

  // Toggle capture with Shift (edge detect)
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    if (!shiftPressed) {
      cursorCaptured = !cursorCaptured;
      glfwSetInputMode(window, GLFW_CURSOR,
                       cursorCaptured ? GLFW_CURSOR_DISABLED
                                      : GLFW_CURSOR_NORMAL);
      if (cursorCaptured) {
        glfwGetCursorPos(window, &lastX, &lastY);
        lastInit = true;
      } else {
        lastInit = false;
      }
      shiftPressed = true;
    }
  } else {
    shiftPressed = false;
  }

  if (cursorCaptured && lastInit) {
    double mouse_x, mouse_y;
    glfwGetCursorPos(window, &mouse_x, &mouse_y);
    double dx = mouse_x - lastX;
    double dy = mouse_y - lastY;
    lastX = mouse_x;
    lastY = mouse_y;

    const float sensitivity = 0.05f;
    eulers.z += -static_cast<float>(dx) * sensitivity;
    eulers.y += -static_cast<float>(dy) * sensitivity;
    eulers.y = fminf(89.0f, fmaxf(-89.0f, eulers.y));
    if (eulers.z > 360.0f)
      eulers.z -= 360.0f;
    if (eulers.z < 0.0f)
      eulers.z += 360.0f;
  }

  return false;
}