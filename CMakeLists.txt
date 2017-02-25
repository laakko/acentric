cmake_minimum_required (VERSION 2.6)

project (music-theory)

include_directories(include)

add_executable (main
	include/Note.h
	src/Note.cpp
	src/main.cpp
)