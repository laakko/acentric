#include "doctest.h"
#include "Note.h"

TEST_CASE("Generic Note tests") {
	Note note1{ BasicNote::A, 0, 4 };
	REQUIRE(note1.getAbsoluteDistance() == 48);
	REQUIRE(note1.getBase() == BasicNote::A);
	
	Note note2 = Note::Note(BasicNote::E, -1, -4);
	REQUIRE(note2.getAbsoluteDistance() == -42);

	REQUIRE(note1.getBasicDistance(note2) == 52);
	REQUIRE(note2.getBasicDistance(note1) == 52);
}