cmake_minimum_required(VERSION 3.10)
project(ScienceEngine)

if(BUILD_EXAMPLES)
add_subdirectory(examples)
endif(BUILD_EXAMPLES)

if(BUILD_TESTS)
add_subdirectory(tests)
endif(BUILD_TESTS)