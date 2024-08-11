cmake_minimum_required(VERSION 3.18)

project(custom_class
	VERSION 0.0.1
	DESCRIPTION "Custom class"
	LANGUAGES C)

link_libraries(objectwrapper)

add_executable(custom_class custom_class.c)