#define STB_IMAGE_IMPLEMENTATION
#include "material.h"
#include "stb/stb_image.h"
#include <glad/glad.h>
#include <iostream>

Material::Material(const char *texturePath) {
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  // Load texture image
  int width, height, channels;
  unsigned char *data =
      stbi_load(texturePath, &width, &height, &channels, STBI_rgb_alpha);

  // Create OpenGL texture
  if (data) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Upload texture data to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);

    // Configure sampler parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  } else {
    std::cerr << "\033[31m[ERROR::TEXTURE]\033[0m Failed to load texture: "
              << texturePath << std::endl;
  }
  stbi_image_free(data);
}

Material::~Material() { glDeleteTextures(1, &textureID); }

void Material::use(int unit) {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, textureID);
}
