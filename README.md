# C++ Learning Projects
 
A collection of small C++ projects built while transitioning into software engineering from a scientific computing background. Each project targets specific concepts relevant to professional C++ development, including object-oriented design, build systems, and static code analysis.
 
## Projects
 
### [particles](./particles/)
A class hierarchy representing particles in a physics simulation. Covers abstract base classes, virtual functions, polymorphism, CMake build system setup, and static analysis with Cppcheck.
 
## Building Any Project
 
Each project contains its own `README.md` with specific build instructions. All projects use CMake and follow the same general pattern:
 
```bash
cd <project-dir>
cmake -S. -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build -j
```
 
## Requirements
 
- C++14 or later
- CMake 3.10 or later
- g++
- Cppcheck (optional, for static analysis)
