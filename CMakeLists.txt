cmake_minimum_required(VERSION 3.13)

project(rlbox_cmake_test
	VERSION 0.1
	DESCRIPTION "RLBox rlbox_cmake_test")

find_package(rlbox-sandboxing-api CONFIG REQUIRED)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(toylib toylib.c)
add_library(toylibwasm toylibwasm.c)
target_include_directories(toylibwasm PRIVATE ${CMAKE_SOURCE_DIR}/wasm2c_sandbox_compiler/wasm2c/)

add_library(wasm-rt-impl wasm2c_sandbox_compiler/wasm2c/wasm-rt-impl.c)
add_library(wasm-rt-wasi wasm2c_sandbox_compiler/wasm2c/wasm-rt-wasi.c)
add_library(wasm-rt-os-unix wasm2c_sandbox_compiler/wasm2c/wasm-rt-os-unix.c)
add_library(wasmsbox SHARED sbox_toylib.cpp)
add_library(sbox SHARED sbox_toylib.cpp)

# generate two .so files
# wasmsbox is the wasm sandbox shared library
# sbox is the noop sandbox shared library
#set_property(TARGET sbox PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(wasmsbox rlbox-sandboxing-api toylibwasm wasm-rt-impl wasm-rt-wasi wasm-rt-os-unix)
target_link_libraries(sbox rlbox-sandboxing-api toylib)
