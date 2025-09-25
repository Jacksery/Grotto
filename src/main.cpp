#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

void error_callback(int error, const char *description) {
  std::cerr << "\033[31m[ERROR::GLFW]\033[0m " << description << std::endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int, char **) {
  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) {
    // Initialization failed
    std::cerr << "\033[31m[ERROR::GLFW]\033[0m Failed to initialize GLFW"
              << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(640, 480, "Grotto", NULL, NULL);
  if (!window) {
    // Window or OpenGL context creation failed
    std::cerr << "\033[31m[ERROR::GLFW]\033[0m Failed to create window"
              << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "\033[31m[ERROR::GLAD]\033[0m Failed to initialize GLAD"
              << std::endl;
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);

  int width{640}, height{480};
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
