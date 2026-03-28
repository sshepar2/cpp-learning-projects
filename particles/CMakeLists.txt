cmake_minimum_required(VERSION 3.10)
project(ParticleSimulation)

# set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set output executable to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# pull in src directory
add_subdirectory(src)

# define executables and src files
# link exectuable, do in src/ instead (moving main.cpp into src/ as well)
#add_executable(simulation main.cpp)
#target_link_libraries(simulation PRIVATE particle_lib)
