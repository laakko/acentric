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

BISON_TARGET (Parser src/Parser.y ${CMAKE_CURRENT_BINARY_DIR}/Parser.cxx
			  COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/Parser.hxx --report=all --report-file=${CMAKE_CURRENT_BINARY_DIR}/ParserStates.log")

FLEX_TARGET  (Lexer src/Lexer.l ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cxx
			  COMPILE_FLAGS --header-file=${CMAKE_CURRENT_BINARY_DIR}/Lexer.hxx)

ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/Lexer.hxx "") # HACK so cmake doesn't panic when the header isn't found

#### Lexer/Parser ("acentric_lang") library
add_library(acentric_lang
	include/Reader.h
	include/Lexer.h
	${CMAKE_CURRENT_BINARY_DIR}/Lexer.hxx
	
	src/Reader.cpp	
	src/Lexer.l
	src/Parser.y
	${CMAKE_CURRENT_BINARY_DIR}/Lexer.cxx
	${CMAKE_CURRENT_BINARY_DIR}/Parser.cxx)
	
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
	src/acentric_lang_interactive.cpp)
target_link_libraries(acentric_lang_interactive acentric_lang)

set_target_properties(acentric_lang acentric_lang_interactive PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON)
