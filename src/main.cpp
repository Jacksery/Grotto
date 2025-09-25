#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>

void error_callback(int error, const char *description) {
  std::cerr << "\033[31m[ERROR::GLFW]\033[0m " << description << std::endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int, char **) {
  // Load in shaders
  std::ifstream file;
  std::stringstream bufferedLines;
  std::string line;

  file.open("../../../src/shaders/vertex.txt");
  if (file.is_open()) {
    while (std::getline(file, line)) {
      std::cout << line << "\n";
    }
    file.close();
  } else {
    std::cerr
        << "\033[31m[ERROR::FILE::SHADER]\033[0m Could not open vertex shader"
        << std::endl;
  }

  glfwSetErrorCallback(error_callback);

  // Initalise GLFW
  if (!glfwInit()) {
    std::cerr << "\033[31m[ERROR::GLFW]\033[0m Failed to initialize GLFW"
              << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a windowed mode window and its OpenGL context
  GLFWwindow *window = glfwCreateWindow(640, 480, "Grotto", NULL, NULL);
  if (!window) {
    std::cerr << "\033[31m[ERROR::GLFW]\033[0m Failed to create window"
              << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window); // Bind the OpenGL context to the window

  // Load OpenGL functions using GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "\033[31m[ERROR::GLAD]\033[0m Failed to initialize GLAD"
              << std::endl;
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);

  // Set up the viewport
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

unsigned int make_module(const std::string &filepath, unsigned int moduleType) {
  std::ifstream file;
  std::stringstream bufferedLines;
  std::string line;

  file.open(filepath);
  if (file.is_open()) {
    while (std::getline(file, line)) {
      bufferedLines << line << "\n";
    }
    file.close();
  } else {
    std::cerr
        << "\033[31m[ERROR::SHADER::FILE]\033[0m Could not open shader file: "
        << filepath << std::endl;
    return 0;
  }

  std::string shaderSource = bufferedLines.str();
  const char *shaderSourceCStr = shaderSource.c_str();
  bufferedLines.str("");
  file.close();

  unsigned int shaderModule = glCreateShader(moduleType);
  glShaderSource(shaderModule, 1, &shaderSourceCStr, NULL);
  glCompileShader(shaderModule);

  int success;
  glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[1024];
    glGetShaderInfoLog(shaderModule, 1024, NULL, infoLog);
    std::cerr << "\033[31m[ERROR::SHADER::COMPILATION_FAILED]\033[0m "
              << infoLog << std::endl;
    return 0;
  }

  return shaderModule;
}