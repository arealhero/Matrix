cmake_minimum_required(VERSION 3.0)

project(MatrixLib)

add_subdirectory(libs/googletest/)

include_directories(include/)

add_executable(Matrix specs/specs.cc)

target_link_libraries(Matrix gtest)

