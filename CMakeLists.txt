cmake_minimum_required(VERSION 3.10.0)
project(Grotto VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(Grotto src/main.cpp src/config.cpp src/glad.c src/systems/cameraSystem.cpp src/systems/motionSystem.cpp src/systems/renderSystem.cpp src/view/shader.cpp src/controller/app.cpp)

target_include_directories(Grotto PRIVATE include)
target_link_libraries(Grotto glfw OpenGL::GL)

# Copy compile_commands.json to the source directory after build
# Used for better integration with some IDEs and tools
add_custom_command(TARGET Grotto POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
    COMMENT "Copying compile_commands.json to the source directory"
)
