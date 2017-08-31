#include "doctest.h"
#include "Note.h"

TEST_CASE("Note constructor tests") {

	Note note;

	REQUIRE_NOTHROW(note = Note(BasicNote::A, 0, 4));
	REQUIRE_NOTHROW(note = Note(BasicNote::B, -1234567, 1234567));
	REQUIRE_NOTHROW(note = Note(BasicNote::C, 1234567, -1234567));

	REQUIRE_NOTHROW(note = Note());
	REQUIRE_THROWS(note = Note(""));

	REQUIRE_NOTHROW(note = Note("A"));
	REQUIRE_NOTHROW(note = Note("A#"));
	REQUIRE_NOTHROW(note = Note("A4"));
	REQUIRE_NOTHROW(note = Note("A#4"));
	REQUIRE_NOTHROW(note = Note("A##4"));
	REQUIRE_NOTHROW(note = Note("A###4"));
	REQUIRE_NOTHROW(note = Note("Abbb4"));
	REQUIRE_NOTHROW(note = Note("Abbb-4"));
	REQUIRE_NOTHROW(note = Note("A#b###b##bbb-123456"));

	REQUIRE_NOTHROW(note = Note("A(#^0)"));
	REQUIRE_NOTHROW(note = Note("A(#^09)"));
	REQUIRE_NOTHROW(note = Note("A(b^0)0"));
	REQUIRE_NOTHROW(note = Note("A(#^012)014"));
	REQUIRE_NOTHROW(note = Note("A(#^0)-0"));
	REQUIRE_NOTHROW(note = Note("A(b^123456)"));
	REQUIRE_NOTHROW(note = Note("A(#^123456)123456"));

	REQUIRE_THROWS(note = Note("A()"));
	REQUIRE_THROWS(note = Note("A(b^-0)"));
	REQUIRE_THROWS(note = Note("A(#^-1)"));
	REQUIRE_THROWS(note = Note("Ab(#^1)12"));
	REQUIRE_THROWS(note = Note("AA"));

}

TEST_CASE("Note math tests") {

	Note note1{ BasicNote::A, 0, 4 };
	Note note2{ BasicNote::E, -1, -4 };

	REQUIRE(note1.getAbsoluteDistance() == 48);
	REQUIRE(note1.getBase() == BasicNote::A);
	REQUIRE(note1.getOffset() == 0);
	REQUIRE(note1.getOctave() == 4);
	
	REQUIRE(note2.getAbsoluteDistance() == -42);

	REQUIRE(note2.getBasicDistance(note1) == 52);
	REQUIRE(note1.getBasicDistance(note2) == 52);

}