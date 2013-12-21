cmake_minimum_required(VERSION 2.6)

project(CatchMe)

set(EXECUTABLE_OUTPUT_PATH bin)

# This makes our project Linux and GCC only, at least until CMake implements better C++11 support...
ADD_DEFINITIONS(
	-std=c++11
	-lncurses
)

file(
	GLOB_RECURSE
	source_files
	src/*
)

# Nom de l'executable et fichiers sources
add_executable(
	CatchMe
	${source_files}
)
