cmake_minimum_required(VERSION 3.15)
project(geometry)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# By default, "install" exports the library into ../export (next to both projects),
# so the second project knows where to find it. Can be overridden with --prefix.
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../export" CACHE PATH "Install prefix" FORCE)
endif()

# Static library: produces libgeometry.a
add_library(${PROJECT_NAME} STATIC
    inc/geometry/geometry.h
    src/geometry.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC inc)

# Export: the .a file goes to export/lib, the header to export/include/geometry
install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION lib)
install(FILES inc/geometry/geometry.h DESTINATION include/geometry)
