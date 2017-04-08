cmake_minimum_required (VERSION 2.6)
add_compile_options(-std=c++14)

project (music-theory)

include_directories(include)

add_executable (main
	include/BasicNote.h
	include/Note.h
	include/Interval.h
	include/BasicScale.h
	include/DiatonicScale.h
	src/Note.cpp
	src/Interval.cpp
	src/DiatonicScale.cpp
	src/main.cpp
)
