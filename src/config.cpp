#include "config/config.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

std::filesystem::path g_executable_dir;
std::string get_absolute_path(const std::filesystem::path &relative_path) {
  std::cout << "Executable directory: " << g_executable_dir << std::endl;
  std::cout << "Relative path: " << relative_path << std::endl;
  std::cout << "Absolute path: "
            << (g_executable_dir / relative_path).lexically_normal()
            << std::endl;
  return (g_executable_dir / relative_path).lexically_normal().string();
}