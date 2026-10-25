cmake_minimum_required(VERSION 3.15)
project(shapes_app)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Where the first project exported the library (lib/ + include/)
set(GEOMETRY_ROOT "${CMAKE_SOURCE_DIR}/../export" CACHE PATH "Folder with the exported geometry library")

# Find the static library file libgeometry.a in the exported folder only
find_library(GEOMETRY_LIB
    NAMES libgeometry.a geometry
    PATHS "${GEOMETRY_ROOT}/lib"
    NO_DEFAULT_PATH
)

if(NOT GEOMETRY_LIB OR NOT EXISTS "${GEOMETRY_ROOT}/include/geometry/geometry.h")
    message(FATAL_ERROR
        "geometry library not found in ${GEOMETRY_ROOT}.\n"
        "Build and install the first project first (see README.md).")
endif()

message(STATUS "Using static library: ${GEOMETRY_LIB}")

add_executable(${PROJECT_NAME} src/main.cpp)

# Header search path for #include <geometry/geometry.h>
target_include_directories(${PROJECT_NAME} PRIVATE "${GEOMETRY_ROOT}/include")

# Link the static library into the executable
target_link_libraries(${PROJECT_NAME} PRIVATE "${GEOMETRY_LIB}")
