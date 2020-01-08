cmake_minimum_required (VERSION 3.0)

project(GLAD)

include_directories(include)
add_library(GLAD src/glad.c)
target_include_directories(GLAD PUBLIC Engine/vendor/lib)