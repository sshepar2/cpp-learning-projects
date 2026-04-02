add_compile_options(-Wall -Wextra)

add_executable(linksim main.cpp BitGenerator.cpp BPSK.cpp Channel.cpp utils.cpp)

target_include_directories(linksim PRIVATE ${CMAKE_SOURCE_DIR}/include)
