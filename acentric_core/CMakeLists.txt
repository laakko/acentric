#### Core library
add_library(acentric_core
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
)
target_include_directories(acentric_core
	PUBLIC include
	PUBLIC ../3rd-party)

#### Demo/testing/debug program (remove later on)
add_executable(acentric_core_main src/main.cpp)
target_link_libraries(acentric_core_main acentric_core)

set_target_properties(acentric_core acentric_core_main PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON)