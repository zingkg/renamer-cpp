cmake_minimum_required(VERSION 2.8)

project(Renamer)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall -g -std=c++11")
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Output/Install)

file(GLOB COMMON_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "Common/*.cpp")
file(GLOB RENAMER_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "Renamer/*.cpp")
add_executable(Renamer ${COMMON_SRC} ${RENAMER_SRC})
set_target_properties(Renamer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Output)

enable_testing(true)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Tests/)
