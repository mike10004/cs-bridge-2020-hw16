cmake_minimum_required(VERSION 3.7)
project(hw16)

add_subdirectory("${PROJECT_SOURCE_DIR}/tests" "${PROJECT_SOURCE_DIR}/tests/cmake-build")

add_subdirectory("${PROJECT_SOURCE_DIR}/q1" "${PROJECT_SOURCE_DIR}/q1/cmake-build")
