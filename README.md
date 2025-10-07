# Grotto 3D Engine
A simple OpenGL 3D engine built with C++ and GLFW, implementing an Entity Component System (ECS) architecture.

## Architecture Overview
### Key Systems

- **Motion System**: Handles physics simulation and entity movement
- **Camera System**: Manages first-person camera controls with mouse look and WASD movement  
- **Render System**: Performs OpenGL rendering with model-view-projection transformations

### Components

- **Transform Component**: Position and rotation in 3D space
- **Render Component**: Mesh and material references for rendering
- **Physics Component**: Velocity vectors for linear and angular motion
- **Camera Component**: Camera orientation vectors (right, up, forwards)

## Dependencies

- [**STB Image integration**](https://github.com/nothings/stb) for texture loading
- [**GLM mathematics library**](https://github.com/g-truc/glm) for 3D transformations
- [**GLAD OpenGL loader**](https://github.com/Dav1dde/glad) for OpenGL function loading
- [**GLFW**](https://www.glfw.org/) for window and input management

## Prerequisites
- CMake ≥ 3.10
- A C++ compiler (tested with G++ 15 and Clang++ 21)
- GLFW library (3.4 tested)
- OpenGL ≥ 3.3

## Project Structure

```
.
├── CMakeLists.txt
├── CMakePresets.json
├── LICENSE.md
├── README.md
├── res                         # Resources that get copied to build directory (needed at runtime)
│   ├── shaders
│   │   ├── fragment.txt
│   │   └── vertex.txt
│   └── textures
│       ├── brick.jpg
│       └── mask.jpg
└── src
    ├── config.cpp              # Frequently used headers
    ├── controller              # Main application implementation
    │   ├── app.cpp
    │   └── app.h
    ├── glad.c                  # GLAD opengl bindings
    ├── main.cpp                # Main entry point for execution
    ├── resources               # Handles runtime assets
    │   └── resourceManager.cpp 
    ├── systems                 # Systems to handle ECS management
    │   ├── cameraSystem.cpp
    │   ├── motionSystem.cpp
    │   └── renderSystem.cpp
    └── view                    # Functions related to making shader program
        └── shader.cpp
```

## Building the Project
1. Clone the repository:
    ```bash
    git clone https://github.com/Jacksery/Grotto
    cd Grotto
    ```
2. Create a build directory and navigate into it:
    ```bash
    mkdir build
    cd build
    ```
3. Run CMake to configure the project:
    ```bash
    cmake ..
    ```
4. Build the project:
    ```bash
    cmake --build .
    ```
5. Run the executable:
    ```bash
    ./OpenGL
    ```

## Controls

- **WASD**: Move camera forward/back/left/right
- **Mouse**: Look around (first-person view)
- **Shift**: Toggle mouse lock
- **ESC**: Exit application

## Issues
If you encounter any issues, please open an issue on the GitHub repository.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE.md) file for details.
