# Wavefront Parser
This is a personal project I made with the goal to see how fast I can load a `.obj` file. The parser was originally programmed in C++ however later changed for C for faster wavefront loading. The current loader only supports a monothread mode however, I may add a multi thread for better performance later.

## Dependencies
- Glad
- GLFW 3.4
- Fast Float
- LibMath (personal math library)

## Other Features
- Perspective camera
- Resource manager
- Shader support (GLSL)

## Future Plans
- Implement multi thread object loading
- Seperate wavefront loader into its own static library
