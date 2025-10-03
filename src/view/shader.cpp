#include "view/shader.h"
#include "config/config.h"
#include "resources/resourceManager.h"

unsigned int makeShader(const std::string &vertex_filepath,
                        const std::string &fragment_filepath) {

  // To store all the shader modules
  std::vector<unsigned int> modules;

  auto &resourceMgr = ResourceManager::getInstance();

  // Add a vertex shader module
  modules.push_back(makeShaderModule(resourceMgr.getAssetPath(vertex_filepath),
                                     GL_VERTEX_SHADER));

  // Add a fragment shader module
  modules.push_back(makeShaderModule(
      resourceMgr.getAssetPath(fragment_filepath), GL_FRAGMENT_SHADER));

  // Attach all the modules then link the program
  unsigned int shader = glCreateProgram();
  for (unsigned int shaderModule : modules) {
    glAttachShader(shader, shaderModule);
  }
  glLinkProgram(shader);

  // Check the linking worked
  int success;
  glGetProgramiv(shader, GL_LINK_STATUS, &success);
  if (!success) {
    char errorLog[1024];
    glGetProgramInfoLog(shader, 1024, NULL, errorLog);
    Logging::Error("SHADER",
                   "Failed to link shader program:\n" + std::string(errorLog));
    return 0;
  }

  // Modules are now unneeded and can be freed
  for (unsigned int shaderModule : modules) {
    glDeleteShader(shaderModule);
  }

  return shader;
}

unsigned int makeShaderModule(const std::string &filepath,
                              unsigned int module_type) {

  std::ifstream file;
  std::stringstream bufferedLines;
  std::string line;

  file.open(filepath);
  if (!file.is_open()) {
    Logging::Error("SHADER", "Failed to open shader file: " + filepath);
    return 0;
  }
  while (std::getline(file, line)) {
    bufferedLines << line << '\n';
  }
  std::string shaderSource = bufferedLines.str();
  const char *shaderSrc = shaderSource.c_str();
  bufferedLines.str("");
  file.close();

  unsigned int shaderModule = glCreateShader(module_type);
  glShaderSource(shaderModule, 1, &shaderSrc, NULL);
  glCompileShader(shaderModule);

  int success;
  glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
  if (!success) {
    char errorLog[1024];
    glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
    Logging::Error("SHADER", "Failed to compile shader module (" + filepath +
                                 "):\n" + std::string(errorLog));
    return 0;
  }

  return shaderModule;
}