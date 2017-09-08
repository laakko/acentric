#include "doctest.h"
#include "Note.h"

TEST_CASE("Note constructor tests") {
	using acentric_core::Note;
	using acentric_core::BasicNote;

	Note note;

	REQUIRE_NOTHROW(note = Note(BasicNote::A, 0, 4));
	REQUIRE_NOTHROW(note = Note(BasicNote::B, -1234567, 1234567));
	REQUIRE_NOTHROW(note = Note(BasicNote::C, 1234567, -1234567));

	REQUIRE_NOTHROW(note = Note());
	REQUIRE_THROWS(note = Note('a'));
	REQUIRE_THROWS(note = Note('H'));

	REQUIRE_NOTHROW(note = Note('A'));
	REQUIRE_NOTHROW(note = Note('A', 1));
	REQUIRE_NOTHROW(note = Note('A', 0, 4));
	REQUIRE_NOTHROW(note = Note('A', 1, 4));
	REQUIRE_NOTHROW(note = Note('A', 2, 4));
	REQUIRE_NOTHROW(note = Note('A', 3, 4));
	REQUIRE_NOTHROW(note = Note('A', -3, 4));
	REQUIRE_NOTHROW(note = Note('A', -3, -4));
	REQUIRE_NOTHROW(note = Note('A', 1, -123456));

}

TEST_CASE("Note math tests") {
	using acentric_core::Note;
	using acentric_core::BasicNote;

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