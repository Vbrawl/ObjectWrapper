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


TestCase(object_test tests/object.c src/object.c)
TestCase(vector_test tests/vector.c src/object.c src/vector.c)