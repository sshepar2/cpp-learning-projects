add_compile_options(-Wall -Wextra)

add_library(signal_lib 
            Signal.cpp
            NoisySignal.cpp
            MovingAverageFilter.cpp
            BandPassFilter.cpp
            utils.cpp)

add_executable(process main.cpp)

target_include_directories(signal_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(process PRIVATE signal_lib)