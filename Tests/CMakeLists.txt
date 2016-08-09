cmake_minimum_required(VERSION 2.8)
include(CTest)

include_directories(${CMAKE_SOURCE_DIR}/Libraries/)
include_directories(${CMAKE_SOURCE_DIR})

file(GLOB COMMON_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_SOURCE_DIR}/Common/*.cpp")
file(GLOB RENAMER_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_SOURCE_DIR}/Renamer/*.cpp")
file(GLOB RENAMER_TESTS_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "Renamer/*.cpp")
file(GLOB RENAMER_MAIN_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_SOURCE_DIR}/Renamer/Main.cpp")
list(REMOVE_ITEM RENAMER_SRC ${RENAMER_MAIN_SRC})
add_executable(RenamerTest "Test.cpp" ${COMMON_SRC} ${RENAMER_SRC} ${RENAMER_TESTS_SRC})
set_target_properties(RenamerTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output)
add_test(NAME RenamerTest COMMAND RenamerTest -s)
