cmake_minimum_required(VERSION 3.18)

project(integer_example
	VERSION 0.0.1
	DESCRIPTION "Integer example"
	LANGUAGES C)


link_libraries(objectwrapper)

add_executable(integer_example integer_example.c)