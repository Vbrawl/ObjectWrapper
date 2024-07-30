cmake_minimum_required(VERSION 3.18)

set(CMAKE_BUILD_TYPE Debug)

project(
	ObjectWrapper
	VERSION 1.0.0
	DESCRIPTION "Objects for C"
	LANGUAGES C)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

include_directories(includes)


# Create the shared library target
add_library(objectwrapper SHARED
	src/object.c
	src/vector.c)
target_include_directories(objectwrapper PUBLIC includes)

set_target_properties(objectwrapper PROPERTIES
		VERSION ${PROJECT_VERSION}
		SOVERSION ${PROJECT_VERSION_MAJOR})



# Add test cases
macro(TestCase name)
add_executable(${name} ${ARGN})
add_test(NAME ${name} COMMAND ./${name})
endmacro()

enable_testing()

TestCase(object_test tests/object.c src/object.c)
TestCase(vector_test tests/vector.c src/object.c src/vector.c)


# Add installation steps
install(TARGETS objectwrapper
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

install(DIRECTORY includes/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})