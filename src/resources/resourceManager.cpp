#include "resources/resourceManager.h"

ResourceManager &ResourceManager::getInstance() {
  static ResourceManager instance;
  return instance;
}

void ResourceManager::initialise(const std::filesystem::path &executablePath) {
  executableDir = executablePath.parent_path();
}

// Returns the absolute path to an asset given its path relative to the res/
// directory
std::string
ResourceManager::getAssetPath(const std::string &relativePath) const {
  return (executableDir / "res" / relativePath).lexically_normal().string();
}