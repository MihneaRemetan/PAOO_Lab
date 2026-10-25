cmake_minimum_required(VERSION 3.10)
project(gradebook)

include_directories(inc)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optional demo: build with -DDEMO_SHALLOW_COPY=ON to see what happens
# when a class owning heap memory relies on the compiler-generated copy.
option(DEMO_SHALLOW_COPY "Build the shallow-copy (double delete) demo" OFF)

add_executable(${PROJECT_NAME}
    inc/gradebook/gradebook_config.hpp
    inc/gradebook/student.hpp
    src/main.cpp
    src/student.cpp
)

if(DEMO_SHALLOW_COPY)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEMO_SHALLOW_COPY)
    # AddressSanitizer reports the double delete clearly instead of a random crash
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address -g)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
endif()
