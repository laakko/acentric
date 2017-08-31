#### Find Flex/Bison
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
			  COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/MusicParser.hxx --report=all --report-file=${CMAKE_CURRENT_BINARY_DIR}/MusicParserStates.log")

FLEX_TARGET  (MusicLexer src/MusicLexer.l ${CMAKE_CURRENT_BINARY_DIR}/MusicLexer.cxx
			  COMPILE_FLAGS --header-file=${CMAKE_CURRENT_BINARY_DIR}/MusicLexer.hxx)

ADD_FLEX_BISON_DEPENDENCY(MusicLexer MusicParser)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/MusicLexer.hxx "") # HACK so cmake doesn't panic when the header isn't found

#### Lexer/Parser ("acentric_lang") library
add_library(acentric_lang
	include/MusicReader.h
	include/MusicLexer.h
	${CMAKE_CURRENT_BINARY_DIR}/MusicLexer.hxx
	
	src/MusicReader.cpp	
	src/MusicLexer.l
	src/MusicParser.y
	${CMAKE_CURRENT_BINARY_DIR}/MusicLexer.cxx
	${CMAKE_CURRENT_BINARY_DIR}/MusicParser.cxx)
	
target_link_libraries(acentric_lang acentric_core)
target_include_directories(acentric_lang
	PUBLIC include
	PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
	
if(WIN32)
	target_include_directories(acentric_lang
		PUBLIC ${FLEX_INCLUDE_DIR})
endif(WIN32)

#### Interactive prompt
add_executable(acentric_lang_interactive
	src/mparse_main.cpp)
target_link_libraries(acentric_lang_interactive acentric_lang)

set_target_properties(acentric_lang acentric_lang_interactive PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON)
