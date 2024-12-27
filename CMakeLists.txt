cmake_minimum_required(VERSION 3.10)
project(OpenGLGame)

set(CMAKE_CXX_STANDARD 14)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/Libraries/include)

# Source files
file(GLOB SOURCES
    *.cpp
    *.c
)

# Add executable
add_executable(OpenGLGame ${SOURCES})

# Link libraries
target_link_libraries(OpenGLGame
    glfw
)
