CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(CatchMe)

SET(EXECUTABLE_OUTPUT_PATH bin)

# This makes our project Linux and GCC only, at least until CMake implements better C++11 support...
ADD_DEFINITIONS(-std=c++11)

FIND_PACKAGE(Boost COMPONENTS system asio FATAL_ERROR)

LINK_DIRECTORIES(${BOOST_LIBRARY_DIRS})
INCLUDE_DIRECTORIES(${BOOST_INCLUDE_DIRS})

FILE(
	GLOB_RECURSE
	source_files
	src/*
)

# Nom de l'executable et fichiers sources
ADD_EXECUTABLE(
	CatchMe
	${source_files}
)

TARGET_LINK_LIBRARIES(CatchMe ${Boost_ASIO_LIBRARIES} ${Boost_SYSTEM_LIBRARY})
