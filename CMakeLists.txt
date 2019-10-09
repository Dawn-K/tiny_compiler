cmake_minimum_required(VERSION 3.14)
project(tiny_compiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(tiny_compiler main.cpp lexical_analysis.cpp lexical_analysis.h)