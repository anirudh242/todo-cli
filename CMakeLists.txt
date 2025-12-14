cmake_minimum_required(VERSION 3.10)
project(TodoCLI)

file(GLOB SOURCES "*.cpp")
add_executable(todo ${SOURCES})

target_include_directories(todo PUBLIC include)
target_compile_features(todo PUBLIC cxx_std_17)

