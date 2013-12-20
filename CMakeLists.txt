cmake_minimum_required(VERSION 2.6)

project(CatchMe)

set(EXECUTABLE_OUTPUT_PATH bin)

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