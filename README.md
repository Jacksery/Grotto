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
├── include/
│   ├── components/          # ECS component definitions
│   │   ├── cameraComponent.h
│   │   ├── physicsComponent.h
│   │   ├── renderComponent.h
│   │   └── transformComponent.h
│   ├── config/
│   │   └── config.h         # Common includes and dependencies
│   ├── logging/
│   │   └── logging.h        # Logging utilities
│   ├── systems/             # ECS system implementations
│   │   ├── cameraSystem.h
│   │   ├── motionSystem.h
│   │   └── renderSystem.h
│   └── view/
│       └── shader.h         # Shader loading utilities
├── src/
│   ├── controller/
│   │   ├── app.h            # Main application class
│   │   └── app.cpp
│   ├── shaders/
│   │   ├── vertex.txt       # Vertex shader
│   │   └── fragment.txt     # Fragment shader
│   ├── systems/             # System implementations
│   └── main.cpp             # Entry point
├── res/
│   └── textures/            # Texture assets
└── build/                   # CMake build directory
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
- **ESC**: Exit application

## Issues
If you encounter any issues, please open an issue on the GitHub repository.

Known issues:
- Ensure assets load correctly by running the executable from the `out/build/$CC` directory. Running it outside of the build directory may lead to asset loading issues — see [Issue #5](https://github.com/Jacksery/Grotto/issues/5) for additional details.


## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE.md) file for details.
