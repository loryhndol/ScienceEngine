cmake_minimum_required(VERSION 3.10)
project(ScienceEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)

add_subdirectory(examples)
if(BUILD_EXAMPLES)
endif(BUILD_EXAMPLES)

if(BUILD_TESTS)
add_subdirectory(tests)
endif(BUILD_TESTS)