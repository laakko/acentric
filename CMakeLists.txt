cmake_minimum_required (VERSION 2.6)
add_compile_options(-std=c++14)

project (music-theory)

include_directories(3rd-party include)

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

add_executable (run-tests
	3rd-party/doctest.h
	
	include/BasicNote.h
	include/Note.h
	include/Interval.h
	
	src/Note.cpp
	src/Interval.cpp
	
	src/tests/NoteTest.cpp
	src/tests/MainTest.cpp
)

find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
	${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY
)
add_custom_target(doc
	${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)
