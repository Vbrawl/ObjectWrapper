cmake_minimum_required(VERSION 3.18)

project(
	ObjectWrapper
	VERSION 2.1.0
	DESCRIPTION "Objects for C"
	LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

if(NOT DEFINED CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_HOST_UNIX)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3")
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

include_directories(includes)


# Create the shared library target
add_library(objectwrapper SHARED
	src/object.c
	src/array.c
	src/ow_string.c
	src/vector.c
	src/map.c
	src/ctypes.c)
target_include_directories(objectwrapper PUBLIC includes)

set_target_properties(objectwrapper PROPERTIES
		VERSION ${PROJECT_VERSION}
		SOVERSION ${PROJECT_VERSION_MAJOR})



# Add test cases
macro(TestCase name)
add_executable(${name} ${ARGN})
add_test(NAME ${name} COMMAND ./${name})
add_test(NAME memcheck_${name} COMMAND valgrind --error-exitcode=1 --leak-check=full ./${name})
endmacro()

enable_testing()

TestCase(object_test tests/object.c src/object.c)
TestCase(vector_test tests/vector.c src/object.c src/vector.c src/array.c src/ctypes.c)
TestCase(string_test tests/ow_string.c src/object.c src/ow_string.c src/array.c)
TestCase(array_test tests/array.c src/object.c src/array.c)
TestCase(map_test tests/map.c src/map.c src/vector.c src/array.c src/object.c src/ow_string.c src/ctypes.c)
TestCase(ctypes_test tests/ctypes.c src/object.c src/ctypes.c)


# Add installation steps
install(TARGETS objectwrapper
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

install(DIRECTORY includes/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
