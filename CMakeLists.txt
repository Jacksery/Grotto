cmake_minimum_required(VERSION 3.10.0)
project(OpenGL VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(OpenGL src/main.cpp src/glad.c)

target_include_directories(OpenGL PRIVATE include)

find_package(glfw3 3.4 REQUIRED)
target_link_libraries(OpenGL glfw)

# Copy compile_commands.json to the source directory after build
# Used for better integration with some IDEs and tools
add_custom_command(TARGET OpenGL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
    COMMENT "Copying compile_commands.json to the source directory"
)
