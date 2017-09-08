option (BUILD_LEXER_AND_PARSER_SOURCE OFF "If selected, CMake will attempt to find Flex and Bison on your system and build the lexer and parser source from the .l and .y files. Otherwise, pre-built lexer and parser source will be used.")

if (BUILD_LEXER_AND_PARSER_SOURCE)
	#### Find Flex/Bison
	# TODO better searching for win_flex.exe and win_bison.exe (don't force using Cygwin)
	if (WIN32)
		message(STATUS "Windows detected, finding Cygwin and flex.exe/bison.exe")

		find_package(cygwin REQUIRED)

		if (EXISTS "${CYGWIN_INSTALL_PATH}/bin/flex.exe")
			set(FLEX_EXECUTABLE "${CYGWIN_INSTALL_PATH}/bin/flex.exe")
		else()
			message(FATAL_ERROR "${CYGWIN_INSTALL_PATH}/bin/flex.exe not found. Reconfigure Cygwin to include Flex to fix this error.")
		endif()
		
		if (EXISTS "${CYGWIN_INSTALL_PATH}/usr/include/FlexLexer.h")
			set(FLEX_INCLUDE_DIR "${CYGWIN_INSTALL_PATH}/usr/include")
		else()
			message(FATAL_ERROR "${CYGWIN_INSTALL_PATH}/usr/include/FlexLexer.h not found. Reconfigure Cygwin to include Flex to fix this error.")
		endif()
		
		if (EXISTS "${CYGWIN_INSTALL_PATH}/bin/bison.exe")
			set(BISON_EXECUTABLE "${CYGWIN_INSTALL_PATH}/bin/bison.exe")
		else()
			message(FATAL_ERROR "${CYGWIN_INSTALL_PATH}/bin/bison.exe not found. Reconfigure Cygwin to include Bison to fix this error.")
		endif()
	endif (WIN32)

	find_package(BISON REQUIRED)
	find_package(FLEX REQUIRED)

	BISON_TARGET (Parser src/Parser.y ${CMAKE_CURRENT_BINARY_DIR}/Parser.cxx
				  COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/Parser.hxx --report=all --report-file=${CMAKE_CURRENT_BINARY_DIR}/ParserStates.log")

	FLEX_TARGET  (Lexer src/Lexer.l ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cxx
				  COMPILE_FLAGS --header-file=${CMAKE_CURRENT_BINARY_DIR}/Lexer.hxx)

	ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/Lexer.hxx "")  # HACK so cmake doesn't panic when the headers aren't found
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/Parser.hxx "") # (flex/bison just haven't generated them yet)

	#### Lexer/Parser ("acentric_lang") library
	add_library(acentric_lang
		include/Reader.h
		include/Lexer.h
		${CMAKE_CURRENT_BINARY_DIR}/Lexer.hxx
		${CMAKE_CURRENT_BINARY_DIR}/Parser.hxx
		
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
else()
	#### Don't mess with Flex/Bison; use prebuilt files instead to make the acentric_lang library
	add_library(acentric_lang
		include/Reader.h
		include/Lexer.h
		flex_bison_prebuilt/Lexer.hxx
		flex_bison_prebuilt/Parser.hxx
		
		src/Reader.cpp
		flex_bison_prebuilt/Lexer.cxx
		flex_bison_prebuilt/Parser.cxx)
		
	target_link_libraries(acentric_lang acentric_core)
	target_include_directories(acentric_lang
		PUBLIC include
		PUBLIC flex_bison_prebuilt
		PUBLIC ../3rd-party)
endif(BUILD_LEXER_AND_PARSER_SOURCE)
	
#### Interactive prompt
add_executable(acentric_lang_interactive
	src/acentric_lang_interactive.cpp)
target_link_libraries(acentric_lang_interactive acentric_lang)

set_target_properties(acentric_lang acentric_lang_interactive PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON)
