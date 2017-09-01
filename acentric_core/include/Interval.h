// Interval.h
#ifndef INTERVAL_H
#define INTERVAL_H

#include <iostream>
#include <string>
#include <vector>

namespace acentric_core {

	class Note;

	/*! The Interval class represents a distance between one Note and another Note.

	An Interval has two components: A basic distance, i.e. number of basic notes from one note to another (*not including the starting note*), and semitone distance.
	For instance, a major third has a basic distance of two and semitone distance of four. A minor sixth has a basic distance of five and semitone distance of eight.

	### Interval Number vs Basic Distance
	In music theory, an interval number represents the *number of notes encompassed* in the interval. For instance, an interval from C4 to D4 would have an interval number of 2.

	This library uses the notion of basic distance, rather than interval number, in its internal representation. This means that, while the *interval number* between C4 and D4 is 2,
	the *basic distance* between C4 and D4 is 1. This facilitates multi-octave calculations. It also helps to maintain consistency with computer science tradition. :)

	Due to potential confusion between the two, it is better to utilize the string-based constructor over the basicDistance/semitones-based constructor unless there is a good reason to do otherwise. */
	class Interval {

	private:
		int basicDistance; // e.g. basic distance from C#4-Eb4 is 2
		int semitones;

	public:
		/*! Standard, non-human-friendly Interval constructor.

		This constructor expects a basic distance (*not* interval number) and a semitone distance. The basic distance is simply the interval number minus one.
		For example, Interval(3, 4) would generate d4, *not* M3 (though both of these intervals are acoustically the same). On the other hand, Interval(2, 4) would generate M3. */
		Interval(int basicDistance, int semitones);

		Interval(char intervalType = 'P', int intervalNumber = 1, int offset = 0);

		/*! Text-based Interval constructor. Recommended for human use.

		There are two main notations: traditional (e.g. M3 for major third, d5 for diminished fifth) or, *far* less commonly,
		parenthesis-based (e.g. (P-5)8, representing a perfect eighth which is lowered by five semitones.

		## Traditional Notation
		Traditional notation expects one of five letters, representing the interval type/name, followed by a positive interval number.

		Valid letters are:
		- P for perfect
		- M for major
		- m for minor
		- A for augmented
		- d for diminished

		The interval number is the number of notes encompassed in the interval. For example, an interval between A4 and E4 would have an interval number of 5.
		An interval between A4 and E5 would have an interval number of 12.

		### Letter Validity
		Not all letters are valid with all numbers. For example, P2 is not a valid musical interval. Refer to a music theory educational source to understand why.
		The [Wikipedia article on intervals](https://en.wikipedia.org/wiki/Interval_(music)) is a good place to start.

		Basically, a letter is valid for a number `n` for the following rules
		- If the letter is P: `n` is valid iff `n mod 7 = 1, 4, or 5`.
		- If the letter is M: `n` is valid iff `n mod 7 = 2, 3, 6, or 7`.
		- If the letter is m: `n` is valid iff `n mod 7 = 2, 3, 6, or 7`.
		- If the letter is A: `n` is valid for all positive integers
		- If the letter is d: `n` is valid for all positive integers except 1 (a d1 interval would result in a negative semitone distance)

		## Parenthesis Notation
		Parenthesis notation is useful (albeit in very niche circumstances) for intervals with disproportionate interval numbers and semitone distances.
		For example, a doubly-augmented sixth would be represented in parenthesis notation as (M+2)6. A triple-augmented fourth would be represented as (P+3)4.
		A quadruple-diminished fifth would be represented as (P-4)5, and so on.

		Parenthesis notation expects the following in order:
		- Open parenthesis
		- P or M
		- Plus (+) or minus (-), representing the direction (augmenting or diminishing) from the P or M
		- A positive integer, representing the number of semitones away from the P or M
		- Close parenthesis
		- A positive integer for the interval number

		As above, P is valid for interval numbers congruent to 1, 4, and 5, (mod 7), and M is valid for interval numbers congruent to 2, 3, 6, and 7 (mod 7).
		m, A, and d are not valid letters in this context; parenthesis notation is based on distance from the perfect or major interval.

		Additionally, no interval with a negative semitone distance is allowed. The interval (P-7)4 will cause an error. */
		Interval(std::string commonName);

		/*! Takes a string of intervals and returns a vector containing, in order, the Intervals in the string. This is useful for building scales and chords.

		This function uses a regular expression to find valid-looking interval names. As such, there is no specific delimeter or string format required.
		For example, makeIntervalVector("M2 M3 P4 P5 M6 M7") and makeIntervalVector("M2, M3...P4: P5---M6. M7") would both behave similarly.

		At the parsing stage, invalid intervals such as P3 or M4 are accepted and passed directly to the Interval constructor, which will then reject them and cause an error.
		For example, makeIntervalVector("M2 P3") would cause an error. */
		static std::vector<Interval> makeIntervalVector(std::string intervals);

		//Interval getInversion() const; // TODO implement

		/*! Returns the interval number of this Interval. For example, if this is a P5 interval, this function will return 5. */
		int getBasicInterval() const { return basicDistance + 1; }

		/*! Returns the basic distance of this Interval. For example, if this is a P5 interval, this function will return 4. */
		int getBasicDistance() const { return basicDistance; }

		/*! Returns the semitone distance of this interval. For examle, if this is a P5 interval, this function will return 7. */
		int getSemitones() const { return semitones; }

		Interval operator+(const Interval& other);

		Interval operator-(const Interval& other);

		// TODO add chromatic intervals, e.g. C4-F4 = i5
	};

	/*! Prints the Interval in human-readable format, choosing from traditional or parenthesis-based format based on the interval distance.

	If a traditional format exists for this interval, the function will prefer that format. If, on the other hand, no traditional format exists
	(e.g. for an interval with interval number 7 and semitone distance 14), the function will use parenthesis format, e.g. (M+3)7. */
	std::ostream& operator<<(std::ostream &os, const Interval &interval);

}

#endif // INTERVAL_H