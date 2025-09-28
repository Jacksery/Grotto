#pragma once

#include <iostream>
#include <string>

namespace Logging {

// Prints an error log message with a given tag and details in red text
inline void Error(const std::string &tag, const std::string &details) {
  std::cerr << "\033[31m[ERROR::" << tag << "]\033[0m " << details << std::endl;
}

// Prints an info log message with a given tag and details in yellow text
inline void Info(const std::string &tag, const std::string &details) {
  std::cout << "\033[33m[INFO::" << tag << "]\033[0m " << details << std::endl;
}

} // namespace Logging