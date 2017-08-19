cmake_minimum_required (VERSION 2.8)
add_compile_options(-std=c++14)

project (music-theory)

find_package(BISON)
find_package(FLEX)

BISON_TARGET (MusicParser src/MusicParser.y ${CMAKE_CURRENT_BINARY_DIR}/MusicParser.cxx
              COMPILE_FLAGS --defines=${CMAKE_CURRENT_BINARY_DIR}/MusicParser.hxx)
FLEX_TARGET  (MusicLexer src/MusicLexer.l ${CMAKE_CURRENT_BINARY_DIR}/MusicLexer.cxx
              COMPILE_FLAGS --header-file=${CMAKE_CURRENT_BINARY_DIR}/MusicLexer.hxx)
ADD_FLEX_BISON_DEPENDENCY(MusicLexer MusicParser)

include_directories(3rd-party include)

add_executable (main
	include/BasicNote.h
	include/Note.h
	include/Interval.h
	include/BasicScale.h
	include/DiatonicScale.h
	include/Chord.h
	include/BasicChord.h
	
	src/Note.cpp
	src/Interval.cpp
	src/DiatonicScale.cpp
	src/Chord.cpp
	src/main.cpp
)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(mparse
    src/mparse_main.cpp
    src/MusicReader.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/MusicParser.cxx
    ${CMAKE_CURRENT_BINARY_DIR}/MusicLexer.cxx
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
