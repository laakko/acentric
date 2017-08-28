cmake_minimum_required (VERSION 2.8)
add_compile_options(-std=c++14)

project (music-theory)

# TODO make all the flex/bison stuff optional
if (WIN32)
	message("Windows detected, finding Cygwin and flex.exe/bison.exe")

	find_package(cygwin REQUIRED)

	# TODO check to make sure the following files exist, error if not (tell user to add flex/bison to cygwin)
	set(FLEX_EXECUTABLE "${CYGWIN_INSTALL_PATH}/bin/flex.exe")
	set(FLEX_INCLUDE_DIR "${CYGWIN_INSTALL_PATH}/usr/include")
	set(FL_LIBRARY "${CYGWIN_INSTALL_PATH}/lib/libfl.a")
	set(BISON_EXECUTABLE "${CYGWIN_INSTALL_PATH}/bin/bison.exe")
endif (WIN32)

find_package(BISON)
find_package(FLEX)

BISON_TARGET (MusicParser src/MusicParser.y ${CMAKE_CURRENT_BINARY_DIR}/MusicParser.cxx
			  COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/MusicParser.hxx --report=state --report-file=${CMAKE_CURRENT_BINARY_DIR}/MusicParserStates.log")

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
if (WIN32)
	include_directories(${FLEX_INCLUDE_DIR})
endif (WIN32)
add_executable(mparse
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
	
    src/mparse_main.cpp
    src/MusicReader.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/MusicParser.cxx
    ${CMAKE_CURRENT_BINARY_DIR}/MusicLexer.cxx
	
	src/MusicLexer.l
	src/MusicParser.y
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
