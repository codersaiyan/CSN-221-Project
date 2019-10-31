cmake_minimum_required(VERSION 3.5)

project(register-renaming LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(register-renaming main.cpp parser.cpp rename.cpp)
