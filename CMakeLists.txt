cmake_minimum_required(VERSION 3.14)
project(complier_test)

set(CMAKE_CXX_STANDARD 11)

add_executable(complier_test main.cpp Lexical_Analysiser.cpp Num_Checker.cpp Num_Checker_LL1.cpp)
add_executable(Reg Reg.cpp)
add_executable(Ava Ava.cpp Ava.cpp)
add_executable(Store StoreTest.cpp Store.cpp Tack.cpp Reg.cpp Prex.cpp)
add_executable(myStack Tack.cpp Tack.cpp)