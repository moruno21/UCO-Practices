cmake_minimum_required (VERSION 3.1)
project (avl_tree)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(test_avltnode test_avltree.cpp avltree.hpp avltree_imp.hpp)
target_compile_definitions(test_avltnode PRIVATE "-D__ONLY_BSTREE__")

add_executable(test_bstree test_avltree.cpp avltree.hpp avltree_imp.hpp)
target_compile_definitions(test_bstree PRIVATE "-D__ONLY_BSTREE__")

add_executable(test_avltree test_avltree.cpp avltree.hpp avltree_imp.hpp)

