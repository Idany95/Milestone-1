cmake_minimum_required(VERSION 3.15)
project(ex3)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex3 ex3.h main.cpp interpreter lexer)