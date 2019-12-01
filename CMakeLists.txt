cmake_minimum_required(VERSION 3.14)
project(complier_test)

set(CMAKE_CXX_STANDARD 11)

add_executable(complier_test main.cpp Lexical_Analysiser.cpp Num_Checker.cpp Num_Checker_LL1.cpp)
#add_executable(complier_scanner main.cpp Lexical_Analysiser.cpp )