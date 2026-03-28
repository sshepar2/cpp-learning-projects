add_library(particle_lib particle.cpp simulation.cpp)

add_executable(simulation main.cpp)

target_include_directories(particle_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(simulation PRIVATE particle_lib)
target_compile_options(particle_lib PRIVATE -Wall -Wextra)