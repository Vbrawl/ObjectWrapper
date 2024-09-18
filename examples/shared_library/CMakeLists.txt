cmake_minimum_required(VERSION 3.18)

project(shared_library
	VERSION 0.0.1
	DESCRIPTION "Shared Library"
	LANGUAGES C)

include_directories(includes)
link_libraries(objectwrapper)

add_library(cslib SHARED
	src/cow_say.c
	src/lib_init.c)

add_executable(say_hi
	prog_src/main.c)

target_link_libraries(say_hi cslib)
