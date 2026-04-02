# C++ Learning Projects
 
A collection of small C++ projects built while transitioning into software engineering from a scientific computing background. Each project targets specific concepts relevant to professional C++ development, including object-oriented design, build systems, and static code analysis.

## Scope and Standards

These projects are written in the context of simulation and ground support software, where standard C++ features including exceptions, STL containers, and dynamic memory allocation are appropriate. They do not follow safety-critical coding standards such as JSF++ or MISRA C++, which apply to flight-certified and embedded systems and impose additional constraints including no exceptions, no dynamic allocation, and bounded loops.

## Projects
 
### [particles](./particles/)
A class hierarchy representing particles in a physics simulation. Covers abstract base classes, virtual functions, polymorphism, CMake build system setup, and static analysis with Cppcheck.

### [signals](./signals/)
A signal processing pipeline that generates synthetic noisy signals and applies moving average or band-pass filtering. The band-pass filter implements a discrete Fourier transform (DFT) and inverse DFT to isolate frequency components. Covers OOP pipeline design, complex number arithmetic, CMake static library linking, signed/unsigned integer handling, error handling, and docstring.
 
### [linksim](./linksim/)
A BPSK digital communications link simulation. Generates random bit sequences, modulates to IQ symbols, transmits through an AWGN channel, and computes BER across a sweep of SNR values. Outputs a BER vs SNR curve for link budget analysis.

## Building Any Project
 
Each project contains its own `README.md` with specific build instructions. All projects use CMake and follow the same general pattern:
 
```bash
cd <project-dir>
cmake -S. -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build -j
```
 
## Requirements
 
- C++17 or later
- CMake 3.10 or later
- g++
- Cppcheck (optional, for static analysis)
- Make (optional, for convenient build/clean)
