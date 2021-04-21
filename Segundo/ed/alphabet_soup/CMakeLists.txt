cmake_minimum_required (VERSION 3.1)
project (alphabet_soup)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
set(CMAKE_CXX_FLAGS "-Wall")

add_executable(test_trie test_trie.cpp trie.cpp trie.hpp)
add_executable(test_alphabet_soup_solver test_alphabet_soup_solver.cpp
    alphabet_soup_solver.cpp alphabet_soup_solver.hpp
    alphabet_soup.cpp alphabet_soup.hpp
    trie.hpp trie.cpp)
