cmake_minimum_required(VERSION 3.10)
project(LinkSimulation)

# set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set output executable to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# pull in src directory
add_subdirectory(src)
