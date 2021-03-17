cmake_minimum_required (VERSION 3.1)
project (check_brackets)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(test_slist test_slist.cpp slist.hpp)
add_executable(test_stack test_stack.cpp stack.hpp)
add_executable(test_check_brackets test_check_brackets.cpp check_brackets.cpp check_brackets.hpp stack.hpp)

