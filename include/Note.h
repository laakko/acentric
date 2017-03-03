// Note.h
#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <iostream>
#include "BasicNote.h"
#include "Interval.h"
class Interval;

class Note{

private:
	BasicNote base;
	int offset;
	int octave;

public:
	Note(BasicNote base = BasicNote::A, int offset = 0, int octave = 4);
	//Note(std::string textNote); // TODO implement

	//Note operator+(int semitones) const; // TODO implement (implicit simplify)
	//Note operator-(int semitones) const; // TODO implement (implicit simplify)
	bool operator>(const Note &other) const { return getAbsoluteDistance() > other.getAbsoluteDistance(); }
	bool operator<(const Note &other) const { return getAbsoluteDistance() < other.getAbsoluteDistance(); }
	// TODO compare values, not names...but is this too confusing?
	// maybe use == for name equality (if it's ever even needed...) and isEnharmonic(const Note &other) const for absolute distance
	bool operator==(const Note &other) const { return getAbsoluteDistance() == other.getAbsoluteDistance(); }
	bool operator<=(const Note &other) const { return getAbsoluteDistance() <= other.getAbsoluteDistance(); }
	bool operator>=(const Note &other) const { return getAbsoluteDistance() >= other.getAbsoluteDistance(); }

	BasicNote getBase() const { return base; }
	int getOffset() const { return offset; }
	int getOctave() const { return octave; }

	// TODO Perhaps these should actually be part of the Interval class
	int getAbsoluteDistance() const; // Distance from A0; returns negative for negative-octave notes
	int getBasicDistance(const Note &other) const;
	int getRelativeDistance(const Note &other) const;

	Note getOtherNote(const Interval &interval, bool getHigherNote = true) const;
	Interval getInterval(const Note &other) const; // TODO test!
	//bool simplify(); // TODO implement e.g. E# -> F, Abb -> G. Return true if something changed
};

std::ostream& operator<<(std::ostream &os, const Note &note);

#endif // NOTE_H