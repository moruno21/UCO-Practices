cmake_minimum_required (VERSION 3.1)
project (dos_detect)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")


include (CheckIncludeFileCXX)
check_include_file_cxx("cstdint" HAVE_CSTDINT)
if ( HAVE_CSTDINT )
    include(CheckTypeSize)
    check_type_size("uint64_t" SIZEOF_UINT64_T)
endif()

if (NOT SIZEOF_UINT64_T EQUAL 8)
    message(FATAL_ERROR "Can't find suitable uint64_t")
endif()

add_executable(test_hash_table test_hash_table.cpp hash_table.hpp ip_utils.hpp)
add_executable(test_dos_detector test_dos_detector.cpp hash_table.hpp ip_utils.hpp dos_detector.hpp dos_detector.cpp)
