# OpenGL 3d Engine
## Example Project Layout
Here is an example project layout to help structure the project:
```
project-root/
├── CMakeLists.txt
├── CMakePresets.json
├── src/
│   ├── main.cpp
│   ├── engine/
│   │   ├── core/
│   │   │   ├── Application.h
│   │   │   ├── Application.cpp
│   │   │   ├── Window.h
│   │   │   ├── Window.cpp
│   │   │   ├── Input.h
│   │   │   └── Input.cpp
│   │   ├── renderer/
│   │   │   ├── Renderer.h
│   │   │   ├── Renderer.cpp
│   │   │   ├── Shader.h
│   │   │   ├── Shader.cpp
│   │   │   ├── Buffer.h
│   │   │   ├── Buffer.cpp
│   │   │   ├── VertexArray.h
│   │   │   └── VertexArray.cpp
│   │   ├── scene/
│   │   │   ├── Scene.h
│   │   │   ├── Scene.cpp
│   │   │   ├── Entity.h
│   │   │   ├── Entity.cpp
│   │   │   ├── Camera.h
│   │   │   └── Camera.cpp
│   │   └── math/
│   │       ├── Vector3.h
│   │       ├── Matrix4.h
│   │       └── Transform.h
│   └── game/
│       ├── Game.h
│       └── Game.cpp
├── assets/
│   ├── shaders/
│   │   ├── basic.vert
│   │   └── basic.frag
│   ├── textures/
│   └── models/
├── third-party/
│   ├── glad/
│   ├── glfw/
│   └── glm/
├── include/
└── lib/
```