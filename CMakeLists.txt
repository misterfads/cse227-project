cmake_minimum_required(VERSION 3.13)

project(rlbox_cmake_test
	VERSION 0.1
	DESCRIPTION "RLBox rlbox_cmake_test")

find_package(rlbox-sandboxing-api CONFIG REQUIRED)

add_library(cmult cmult.c)
add_library(sbox SHARED sbox_cmult.cpp)

#add_executable(main main.cpp)
target_link_libraries(sbox rlbox-sandboxing-api cmult)
