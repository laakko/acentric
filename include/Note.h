// Note.h
#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string>
#include "BasicNote.h"
#include "Interval.h"

/*! The Note class is the basic building block for the music-theory library.

 * A Note consists of three elements: the basic letter name of the note, i.e. A, B, C, D, E, F, or G; 
 * the offset, which is the number of sharps or flats after the note (usually just one sharp or one flat, but an integer number is supported);
 * and the octave number, which can be any integer value (but is limited in practice to positive values slightly above zero). */
class Note{ // TODO make Note/Interval friends?

private:
	BasicNote base;
	int offset;
	int octave;

public:
	Note(BasicNote base = BasicNote::A, int offset = 0, int octave = 4);

	/*! Text-based Note constructor.
	 *
	 * There are two main notations: traditional (e.g. A#4 or Bb2) or parenthesis-based.
	 * Traditional notation expects a basic letter name of the note, a number of sharps or flats, and an octave.
	 * If only a letter name is given, it is assumed there is no sharp/flat offset, and the octave is assumed to be 4.
	 * A few accepted examples of traditional notation:
	 * - A4
	 * - Cb
	 * - F##0
	 * - B####-23 (a B-quadruple-sharp, i.e. D-sharp, in octave -23)
	 *
	 * (It is also possible to mix multiple sharps and flats in any order; sharps and flats cancel one another out. This usage is expected to be very limited.)
	 *
	 * Parenthesis notation is designed for scientific or otherwise academic use. It allows compact notation of Notes with many sharps or flats.
	 * The parenthesis notation expects the following in order:
	 * - Basic letter name
	 * - Open parenthesis
	 * - # or b
	 * - ^
	 * - Positive integer
	 * - Close parenthesis
	 * - (optional) Integer octave number
	 * A few accepted examples of parenthesis notation:
	 * - A(b^3)4
	 * - F(#^10)-1
	 * - C(#^450)300
	 * - B(b^10385)-981745 */
	Note(const std::string & textNote); // TODO clean up, it's really ugly

	/*! Returns a Note based on the given interval being added to this note.
	 * For example, Note("C4") + Interval("M3") evaluates to Note("F4"). */
	Note operator+(Interval interval) const;

	/*! Returns a Note based on the given interval being subtracted from this note.
	 * For example, Note("C4") - Interval("M3") evaluates to Note("G3"). */
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

	BasicNote getBase() const { return base; }
	int getOffset() const { return offset; }
	int getOctave() const { return octave; }

	// TODO Perhaps these should actually be part of the Interval class
	int getAbsoluteDistance() const; // Distance from A0; returns negative for negative-octave notes
	int getBasicDistance(const Note &other) const;
	int getSemitoneDistance(const Note &other) const;

	Note getOtherNote(const Interval &interval, bool getLowerNote = false) const;
	Interval getInterval(const Note &other) const;

};

std::ostream& operator<<(std::ostream &os, const Note &note);

#endif // NOTE_H