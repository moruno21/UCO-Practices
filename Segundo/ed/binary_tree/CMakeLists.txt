cmake_minimum_required (VERSION 3.1)
project (binary_tree)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(test_btree test_btree.cpp btree.hpp btree_utils.hpp)
