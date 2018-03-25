
cmake_minimum_required(VERSION 3.5)
project(task_4)

set(CMAKE_CXX_COMPILER g++)
#set(CMAKE_4_COMPILER g++)
#set(CMAKE_4_COMPILER_ENV_VAR g++)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -pedantic")

include_directories("${PROJECT_BINARY_DIR}")
add_executable(task_4 task_4.cpp  instance.cpp item.cpp knapsack.cpp solver.cpp stdafx.cpp)

target_compile_options(task_4 PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++14>)
