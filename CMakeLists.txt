cmake_minimum_required(VERSION 3.28)
project(ParticleSystem)

set(CMAKE_CXX_STANDARD 17)


set(EXT_DIR "${CMAKE_SOURCE_DIR}/external")

#GLFW 3.4
add_subdirectory(${EXT_DIR}/glfw-3.4)
include_directories(${EXT_DIR}/glfw-3.4/include)

#GLM 1.0.1
add_subdirectory(${EXT_DIR}/glm-1.0.1)
include_directories(${EXT_DIR}/glm-1.0.1)

#GLAD
add_subdirectory(${EXT_DIR}/glad)
include_directories(${EXT_DIR}/glad/include)


set(HEADER_FILES DisplayManager.hpp)

set(SOURCE_FILES DisplayManager.cpp
        Particles.cpp
        Particles.hpp)

add_executable(ParticleSystem main.cpp ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(ParticleSystem PUBLIC glfw glm glad -static)