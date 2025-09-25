#include "triangle_mesh.h"

#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void error_callback(int error, const char *description) {
  std::cerr << "\033[31m[ERROR::GLFW]\033[0m " << description << std::endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

unsigned int makeShaderModule(const std::string &filepath,
                              unsigned int moduleType);
unsigned int makeShader(const std::string &vertexFilePath,
                        const std::string &fragmentFilePath);

int main(int, char **) {
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
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  // Create a triangle mesh
  TriangleMesh *triangleMesh = new TriangleMesh();

  // Create and compile shaders
  // Currently based on executing from `./out/build/clang-21/`
  unsigned int shaderProgram = makeShader("../../../src/shaders/vertex.txt",
                                          "../../../src/shaders/fragment.txt");
  if (shaderProgram == 0) {
    std::cerr
        << "\033[31m[ERROR::SHADER]\033[0m Failed to create shader program"
        << std::endl;
    return -1;
  }

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    triangleMesh->draw();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteProgram(shaderProgram);
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

unsigned int makeShader(const std::string &vertexFilePath,
                        const std::string &fragmentFilePath) {
  std::vector<unsigned int> shaderModules;
  shaderModules.push_back(makeShaderModule(vertexFilePath, GL_VERTEX_SHADER));
  shaderModules.push_back(
      makeShaderModule(fragmentFilePath, GL_FRAGMENT_SHADER));

  unsigned int program = glCreateProgram();
  for (unsigned int shaderModule : shaderModules) {
    glAttachShader(program, shaderModule);
  }
  glLinkProgram(program);

  int success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[1024];
    glGetProgramInfoLog(program, 1024, NULL, infoLog);
    std::cerr << "\033[31m[ERROR::SHADER::LINKING_FAILED]\033[0m " << infoLog
              << std::endl;
    return 0;
  }

  for (unsigned int shaderModule : shaderModules) {
    glDeleteShader(shaderModule);
  }

  return program;
}

unsigned int makeShaderModule(const std::string &filepath,
                              unsigned int moduleType) {
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