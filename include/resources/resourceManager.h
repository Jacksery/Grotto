#pragma once
#include <filesystem>
#include <string>

class ResourceManager {
public:
  // Singleton access
  static ResourceManager &getInstance();

  void initialise(const std::filesystem::path &executablePath);

  // Get absolute paths for assets and shaders
  std::string getAssetPath(const std::string &relativePath) const;
  std::string getShaderPath(const std::string &relativePath) const;

  // Delete copy constructor and assignment
  ResourceManager(const ResourceManager &) = delete;
  ResourceManager &operator=(const ResourceManager &) = delete;

private:
  // Private constructor for singleton
  ResourceManager() = default;
  std::filesystem::path executableDir;
};