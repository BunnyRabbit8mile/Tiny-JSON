cmake_minimum_required (VERSION 3.10)
project (tinyjson)

add_library(tinyjson tinyjson.cxx)
add_executable(tinyjson_test test.cxx)
target_link_libraries(tinyjson_test tinyjson)




