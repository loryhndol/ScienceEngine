add_executable(test_vector test_vector.cc)

target_include_directories(test_vector PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_vector PRIVATE Arch Graph)
