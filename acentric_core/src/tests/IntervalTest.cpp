#include "doctest.h"
#include "Interval.h"
#include "Note.h"

TEST_CASE("Interval constructor tests") {
	using acentric_core::Interval;

	Interval interval;

	// m
	REQUIRE_THROWS(interval = Interval('m', -1));
	REQUIRE_THROWS(interval = Interval('m', 0));
	REQUIRE_THROWS(interval = Interval('m', 1));
	REQUIRE_NOTHROW(interval = Interval('m', 2));
	REQUIRE_NOTHROW(interval = Interval('m', 3));
	REQUIRE_THROWS(interval = Interval('m', 4));
	REQUIRE_THROWS(interval = Interval('m', 5));
	REQUIRE_NOTHROW(interval = Interval('m', 6));
	REQUIRE_NOTHROW(interval = Interval('m', 7));
	REQUIRE_THROWS(interval = Interval('m', 8));
	REQUIRE_NOTHROW(interval = Interval('m', 9));
	REQUIRE_NOTHROW(interval = Interval('m', 10));
	REQUIRE_THROWS(interval = Interval('m', 11));
	REQUIRE_THROWS(interval = Interval('m', 12));
	REQUIRE_NOTHROW(interval = Interval('m', 13));
	REQUIRE_NOTHROW(interval = Interval('m', 14));
	REQUIRE_THROWS(interval = Interval('m', 15));

	// M
	REQUIRE_THROWS(interval = Interval('M', -1));
	REQUIRE_THROWS(interval = Interval('M', 0));
	REQUIRE_THROWS(interval = Interval('M', 1));
	REQUIRE_NOTHROW(interval = Interval('M', 2));
	REQUIRE_NOTHROW(interval = Interval('M', 3));
	REQUIRE_THROWS(interval = Interval('M', 4));
	REQUIRE_THROWS(interval = Interval('M', 5));
	REQUIRE_NOTHROW(interval = Interval('M', 6));
	REQUIRE_NOTHROW(interval = Interval('M', 7));
	REQUIRE_THROWS(interval = Interval('M', 8));
	REQUIRE_NOTHROW(interval = Interval('M', 9));
	REQUIRE_NOTHROW(interval = Interval('M', 10));
	REQUIRE_THROWS(interval = Interval('M', 11));
	REQUIRE_THROWS(interval = Interval('M', 12));
	REQUIRE_NOTHROW(interval = Interval('M', 13));
	REQUIRE_NOTHROW(interval = Interval('M', 14));
	REQUIRE_THROWS(interval = Interval('M', 15));

	// P
	REQUIRE_THROWS(interval = Interval('P', -1));
	REQUIRE_THROWS(interval = Interval('P', 0));
	REQUIRE_NOTHROW(interval = Interval('P', 1));
	REQUIRE_THROWS(interval = Interval('P', 2));
	REQUIRE_THROWS(interval = Interval('P', 3));
	REQUIRE_NOTHROW(interval = Interval('P', 4));
	REQUIRE_NOTHROW(interval = Interval('P', 5));
	REQUIRE_THROWS(interval = Interval('P', 6));
	REQUIRE_THROWS(interval = Interval('P', 7));
	REQUIRE_NOTHROW(interval = Interval('P', 8));
	REQUIRE_THROWS(interval = Interval('P', 9));
	REQUIRE_THROWS(interval = Interval('P', 10));
	REQUIRE_NOTHROW(interval = Interval('P', 11));
	REQUIRE_NOTHROW(interval = Interval('P', 12));
	REQUIRE_THROWS(interval = Interval('P', 13));
	REQUIRE_THROWS(interval = Interval('P', 14));
	REQUIRE_NOTHROW(interval = Interval('P', 15));

	// d
	REQUIRE_THROWS(interval = Interval('d', -1));
	REQUIRE_THROWS(interval = Interval('d', 0));
	REQUIRE_THROWS(interval = Interval('d', 1)); // "gotcha" case...semitone distance is -1
	REQUIRE_NOTHROW(interval = Interval('d', 2));

	// a
	REQUIRE_THROWS(interval = Interval('a', -1));
	REQUIRE_THROWS(interval = Interval('a', 0));
	REQUIRE_NOTHROW(interval = Interval('a', 1));
	REQUIRE_NOTHROW(interval = Interval('a', 2));

}

TEST_CASE("Interval math tests") {
	using acentric_core::Interval;

	Interval m3{ 'm', 3 };
	Interval M3{ 'M', 3 };
	Interval P5{ 'P', 5 };

	REQUIRE_THROWS(m3 - M3);
	REQUIRE_THROWS(M3 - P5);

	Interval res1{ M3 + m3 };
	REQUIRE(res1.getBasicDistance() == 4);
	REQUIRE(res1.getBasicInterval() == 5);
	REQUIRE(res1.getSemitones() == 7);

	Interval res2{ P5 - M3 };
	REQUIRE(res2.getBasicDistance() == 2);
	REQUIRE(res2.getBasicInterval() == 3);
	REQUIRE(res2.getSemitones() == 3);

}