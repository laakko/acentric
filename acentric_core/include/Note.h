// Note.h
#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string>
#include "BasicNote.h"
#include "Interval.h"

namespace acentric_core {

	/*! The Note class is the basic building block for the music-theory library.

	 A Note consists of three elements: the basic letter name of the note, i.e. A, B, C, D, E, F, or G;
	 the offset, which is the number of sharps or flats after the note (usually just one sharp or one flat, but an integer number is supported);
	 and the octave number, which can be any integer value (but is limited in practice to positive values slightly above zero). */
	class Note { // TODO make Note/Interval friends?

	private:
		BasicNote base;
		int offset;
		int octave;

	public:
		/*! Standard, non-human-friendly Note constructor. Defaults to A, with no sharps or flats, in the fourth octave. */
		Note(BasicNote base = BasicNote::A, int offset = 0, int octave = 4);

		/*! An alternative constructor. base must be A, B, C, D, E, F, or G (case sensitive). */
		Note(char base, int offset = 0, int octave = 4);

		/*! Text-based Note constructor. Slightly more human friendly than the standard constructor :)

		There are two main notations: traditional (e.g. A#4 or Bb2) or, *far* less commonly, parenthesis-based (e.g. A(b^5)3 or G(#^3)2).

		## Traditional Notation
		Traditional notation expects a basic letter name of the note, a number of sharps or flats, and an octave.
		If only a letter name is given, it is assumed there is no sharp/flat offset, and the octave is assumed to be 4.

		A few valid examples of traditional notation:
		- A4
		- Cb
		- F##0
		- B####-23 (a B-quadruple-sharp, i.e. D-sharp, in octave -23; internally, this is represented with a base of B, an offset of 4, and an octave of -23.)

		(It is also possible to mix multiple sharps and flats in any order; sharps and flats cancel one another out. The vast majority of people will never use this.)

		## Parenthesis notation
		Parenthesis notation is designed for scientific or otherwise academic use. It allows compact notation of Notes with many sharps or flats.
		The parenthesis notation expects the following in order:
		- Basic letter name
		- Open parenthesis
		- # or b
		- ^
		- Positive integer
		- Close parenthesis
		- (optional) Integer octave number

		A few valid examples of parenthesis notation:
		- A(b^3)4
		- F(#^10)-1
		- C(#^450)300
		- B(b^10385)-981745

		In either notation, *the letter name must be given as a capital letter* to avoid ambiguity with the lower-case b character. (Is bbb b-double-flat, or is it just three flats?)
		This limitation may be eased in the future. */
		Note(const std::string & textNote); // TODO clean up, it's really ugly

		/*! Returns a Note based on the given interval being added to this note.
		For example, Note("C4") + Interval("M3") evaluates to Note("F4"). */
		Note operator+(Interval interval) const;

		/*! Returns a Note based on the given interval being subtracted from this note.
		For example, Note("C4") - Interval("M3") evaluates to Note("G3"). */
		Note operator-(Interval interval) const;

		/*! Evaluates, based on absolute semitone distance from A0, whether this Note is greater in pitch than some other Note. */
		bool operator>(const Note &other) const { return getAbsoluteDistance() > other.getAbsoluteDistance(); }

		/*! Evaluates, based on absolute semitone distance from A0, whether this Note is less in pitch than some other Note. */
		bool operator<(const Note &other) const { return getAbsoluteDistance() < other.getAbsoluteDistance(); }

		/*! Evaluates, based on absolute semitone distance from A0, whether this Note is less than or equal in pitch to some other Note. */
		bool operator<=(const Note &other) const { return getAbsoluteDistance() <= other.getAbsoluteDistance(); }

		/*! Evaluates, based on absolute semitone distance from A0, whether this Note is greather than or equal in pitch to some other Note. */
		bool operator>=(const Note &other) const { return getAbsoluteDistance() >= other.getAbsoluteDistance(); }

		/*! Evaluates whether this note represents the same pitch as the other note.
		 * For example, Note("C#4").isEnharmonic(Note("Db4") evaluates to true. */
		bool isEnharmonic(const Note &other) const { return getAbsoluteDistance() == other.getAbsoluteDistance(); }

		/*! Returns the base of the note as a BasicNote. */
		BasicNote getBase() const { return base; }

		/*! Returns the sharp/flat offset of the note. A positive number indicates the number of sharps, and a negative number indicates the number of flats.
		For example, an offset of 1 represents a single sharp, and an offset of -1 represents a single flat. */
		int getOffset() const { return offset; }

		/*! Returns the octave of the note. Octaves are based on [scientific pitch notation](https://en.wikipedia.org/wiki/Scientific_pitch_notation). */
		int getOctave() const { return octave; }

		// TODO Perhaps these distance and interval functions should actually be part of the Interval class?

		/*! Returns the number of semitones away from A0 this note sits.
		For example, A4 has an absolute distance of 48. C5 has an absolute distance of 63.

		Negative-octave notes return negative values. For example, A#-1 has an absolute distance of -11.
		This may be changed in the future, since the concept of "negative distance" does not make much sense intuitively, but it assists other functions in this case. */
		int getAbsoluteDistance() const;

		/*! Returns the basic note-name distance from this note to the other note.
		For example, the basic distance from A3 to C4 is 14.

		Unlike getAbsoluteDistance(), this function always returns a positive value. For example, the distance from C5 to B4 is *positive* 13. */
		int getBasicDistance(const Note &other) const;

		/*! Returns the number of semitones away from the other note this note sits.
		For example, the semitone distance from E4 to A5 is 5.

		Unlike getAbsoluteDistance(), this function always returns a positive value. For example, the semitone distance from B2 to F1 is 6. */
		int getSemitoneDistance(const Note &other) const;

		/*! Given an Interval, returns the other note to which the given interval goes from this note.
		For example, if this Note is G3 and the Interval is P5 (perfect fifth), the returned Note would be D4.

		Optionally, the lower note can be requested. In this case, the interval travels "downward."
		For example, if this Note is G3, the Interval is P5 (perfect fifth), and the lower note is requested, the returned Note would be C3. */
		Note getOtherNote(const Interval &interval, bool getLowerNote = false) const;

		/*! Given a Note, returns the Interval between this note and the other note.
		For example, if this Note is B4 and the other Note is G4, the returned Interval would be m6 (minor sixth).

		This also works for lower notes.
		For example, if this Note is E4 and the other Note is F3, the returned Interval would be M7 (major seventh). */
		Interval getInterval(const Note &other) const;

	};

	/*! Prints the Note in human-readable format, choosing between traditional or parenthesis-based representation based on the number of sharps or flats in the Note.
	If the Note has two flats, one flat, no sharps/flats, one sharp, or two sharps, then the function will use traditional notation, e.g. F#4 or Bbb3.

	If the number of sharps or flats falls outside this range, then this function will use parenthesis-based representation, e.g. A(#^3)4 or F(b^6)-2. */
	std::ostream& operator<<(std::ostream &os, const Note &note);

}

#endif // NOTE_H