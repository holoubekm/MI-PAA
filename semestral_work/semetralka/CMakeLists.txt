
cmake_minimum_required(VERSION 3.5)
project(semestralka)

set(CMAKE_CXX_COMPILER g++)
#set(CMAKE_4_COMPILER g++)
#set(CMAKE_4_COMPILER_ENV_VAR g++)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -pedantic")

include_directories("${PROJECT_BINARY_DIR}")
add_executable(semestralka semestralka.cpp instance.cpp item.cpp clause.cpp sat3.cpp solver.cpp stdafx.cpp)

target_compile_options(semestralka PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++14>)
