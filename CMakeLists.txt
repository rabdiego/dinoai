# Project details
cmake_minimum_required(VERSION 3.7)
project(DinoAI)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Custom libraries
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS "libs/*.hpp" "libs/*.cpp" )
include_directories(${CMAKE_SOURCE_DIR})
include_directories (/usr/include/freetype2)

add_library(nn
    ${LIB_SOURCES}/nn/
)

add_library(dino
    ${LIB_SOURCES}/dino/
)

# External libraries
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

# Executable
add_executable(train src/train.cpp)
add_executable(play src/play.cpp)
add_executable(pvc src/pvc.cpp)

# Linkers
target_link_libraries(nn ${ARMADILLO_LIBRARIES})
target_link_libraries(dino nn sfml-graphics)
target_link_libraries(train sfml-graphics nn dino)
target_link_libraries(play sfml-graphics nn dino)
target_link_libraries(pvc sfml-graphics nn dino)

# Install
install(TARGETS train)
install(TARGETS play)
install(TARGETS pvc)