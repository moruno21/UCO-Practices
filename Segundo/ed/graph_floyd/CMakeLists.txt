cmake_minimum_required (VERSION 3.1)
project (graphs-floyd)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_DEBUG_FLAGS "-O0 -ggdb3")
add_executable(test_floyd test_floyd.cpp floyd_algorithm.hpp graph.hpp graph_utils.hpp city.hpp city.cpp)

