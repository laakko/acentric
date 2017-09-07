cmake_minimum_required (VERSION 3.1)

project(acentric)

add_subdirectory(acentric_core)
add_subdirectory(acentric_lang)

#add_executable (run-tests
#	3rd-party/doctest.h
	
#	include/BasicNote.h
#	include/Note.h
#	include/Interval.h
	
#	src/Note.cpp
#	src/Interval.cpp
	
#	src/tests/NoteTest.cpp
#	src/tests/MainTest.cpp
#)

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