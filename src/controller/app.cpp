#include "app.h"
#include "config/config.h"
#include "glm/fwd.hpp"
#include "stb/stb_image.h"

#include <chrono>
#include <thread>

App::App() { initGLFW(); };

App::~App() {
  glDeleteBuffers(VBOs.size(), VBOs.data());
  glDeleteVertexArrays(VAOs.size(), VAOs.data());
  glDeleteTextures(textures.size(), textures.data());
  glDeleteProgram(shader);

  delete motionSystem;
  delete cameraSystem;
  delete renderSystem;

  glfwTerminate();
}

unsigned int App::makeEntity() { return entityCount++; }

unsigned int App::makeCubeMesh(glm::vec3 size) {
  float l = size.x;
  float w = size.y;
  float h = size.z;

  std::vector<float> vertices = {
      // pos: x, y, z texCoord: u, v
      l,  w,  -h, 1.0f, 1.0f, l,  -w, -h, 1.0f, 0.0f, -l, -w, -h, 0.0f, 0.0f,
      -l, -w, -h, 0.0f, 0.0f, -l, w,  -h, 0.0f, 1.0f, l,  w,  -h, 1.0f, 1.0f,

      -l, -w, h,  0.0f, 0.0f, l,  -w, h,  1.0f, 0.0f, l,  w,  h,  1.0f, 1.0f,
      l,  w,  h,  1.0f, 1.0f, -l, w,  h,  0.0f, 1.0f, -l, -w, h,  0.0f, 0.0f,

      -l, w,  h,  1.0f, 1.0f, -l, w,  -h, 1.0f, 0.0f, -l, -w, -h, 0.0f, 0.0f,
      -l, -w, -h, 0.0f, 0.0f, -l, -w, h,  0.0f, 1.0f, -l, w,  h,  1.0f, 1.0f,

      l,  -w, -h, 0.0f, 0.0f, l,  w,  -h, 1.0f, 0.0f, l,  w,  h,  1.0f, 1.0f,
      l,  w,  h,  1.0f, 1.0f, l,  -w, h,  0.0f, 1.0f, l,  -w, -h, 0.0f, 0.0f,

      -l, -w, -h, 0.0f, 0.0f, l,  -w, -h, 1.0f, 0.0f, l,  -w, h,  1.0f, 1.0f,
      l,  -w, h,  1.0f, 1.0f, -l, -w, h,  0.0f, 1.0f, -l, -w, -h, 0.0f, 0.0f,

      l,  w,  h,  1.0f, 1.0f, l,  w,  -h, 1.0f, 0.0f, -l, w,  -h, 0.0f, 0.0f,
      -l, w,  -h, 0.0f, 0.0f, -l, w,  h,  0.0f, 1.0f, l,  w,  h,  1.0f, 1.0f};

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  VAOs.push_back(VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  VBOs.push_back(VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
               vertices.data(), GL_STATIC_DRAW);
  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (void *)0);
  glEnableVertexAttribArray(0);
  // texture coordinates
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void *)12);
  glEnableVertexAttribArray(1);

  return VAO;
}

unsigned int App::makeTexture(const char *filename) {
  int width, height, channels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data =
      stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

  if (!data) {
    Logging::Error("STB_IMAGE",
                   "Failed to load texture: " + std::string(filename));
    return 0;
  }

  // make the texture
  unsigned int texture;
  glGenTextures(1, &texture);
  textures.push_back(texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // load data
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);

  // free data
  stbi_image_free(data);

  // Configure sampler
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return texture;
}

void App::run() {
  float update_dt = 16.67f / 1000.0f; // 60 fps
  while (!glfwWindowShouldClose(window)) {
    // Process update logic
    motionSystem->update(transformComponents, physicsComponents, update_dt);
    bool should_close = cameraSystem->update(transformComponents, cameraID,
                                             *cameraComponent, update_dt);
    if (should_close) {
      break;
    }

    renderSystem->update(transformComponents, renderComponents);

    // Centralized buffer swap and event polling to avoid re-entrant polling
    glfwSwapBuffers(window);
    glfwPollEvents();

    // If window is inactive (iconified/unfocused) sleep to reduce CPU
    if (!isActive) {
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  }
}

void App::initGLFW() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

  window = glfwCreateWindow(640, 480, "Grotto", NULL, NULL);
  if (window == NULL) {
    Logging::Error("GLFW", "Failed to create GLFW window");
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  // register callbacks and load GL
  glfwSetWindowUserPointer(window, this);
  glfwSetFramebufferSizeCallback(window, [](GLFWwindow *win, int w, int h) {
    App *app = static_cast<App *>(glfwGetWindowUserPointer(win));
    if (app)
      app->handleResize(w, h);
  });
  glfwSetWindowFocusCallback(window, [](GLFWwindow *win, int focused) {
    App *app = static_cast<App *>(glfwGetWindowUserPointer(win));
    if (app)
      app->setActive(focused != 0);
  });

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Logging::Error("GLAD", "Failed to initialize GLAD");
    glfwTerminate();
  }
}

void App::initOpenGL() {
  glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  shader = makeShader("shaders/vertex.txt", "shaders/fragment.txt");
  if (shader == 0) {
    Logging::Error("APP", "Failed to create shader, exiting");
    glfwTerminate();
    exit(-1);
  }

  glUseProgram(shader);

  // Set initial projection to match current framebuffer size
  int w, h;
  glfwGetFramebufferSize(window, &w, &h);
  handleResize(w, h);
}

void App::handleResize(int width, int height) {
  if (height <= 0)
    return;
  glViewport(0, 0, width, height);
  if (shader == 0)
    return;
  glUseProgram(shader);
  int projLoc = glGetUniformLocation(shader, "projection");
  if (projLoc == -1)
    return;
  glm::mat4 projection = glm::perspective(
      glm::radians(45.0f),
      static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void App::setActive(bool active) { isActive = active; }

void App::initSystems() {
  motionSystem = new MotionSystem();
  cameraSystem = new CameraSystem(shader, window);
  renderSystem = new RenderSystem(shader, window);
}