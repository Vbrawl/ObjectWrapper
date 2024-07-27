cmake_minimum_required(VERSION 3.18)

set(CMAKE_BUILD_TYPE Debug)

project(
	2dgEngine
	LANGUAGES C)


include_directories(includes)


add_executable(dg_object_test tests/dg_object.c src/dg_object.c)


enable_testing()

add_test(
	NAME dg_object_test
	COMMAND ./dg_object_test)