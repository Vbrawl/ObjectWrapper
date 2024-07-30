cmake_minimum_required(VERSION 3.18)

set(CMAKE_BUILD_TYPE Debug)

project(
	2dgEngine
	LANGUAGES C)


include_directories(includes)

enable_testing()

macro(TestCase name)
add_executable(${name} ${ARGN})
add_test(NAME ${name} COMMAND ./${name})
endmacro()


TestCase(dg_object_test tests/dg_object.c src/dg_object.c)