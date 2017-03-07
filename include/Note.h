// Note.h
#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string>
#include "BasicNote.h"
#include "Interval.h"

class Note{

private:
	BasicNote base;
	int offset;
	int octave;

public:
	Note(BasicNote base = BasicNote::A, int offset = 0, int octave = 4);
	//Note(std::string textNote); // TODO implement

	//Note operator+(int semitones) const; // TODO implement (implicit simplify)
	Note operator+(Interval interval) const;
	//Note operator-(int semitones) const; // TODO implement (implicit simplify)
	Note operator-(Interval interval) const;
	bool operator>(const Note &other) const { return getAbsoluteDistance() > other.getAbsoluteDistance(); }
	bool operator<(const Note &other) const { return getAbsoluteDistance() < other.getAbsoluteDistance(); }
	bool operator<=(const Note &other) const { return getAbsoluteDistance() <= other.getAbsoluteDistance(); }
	bool operator>=(const Note &other) const { return getAbsoluteDistance() >= other.getAbsoluteDistance(); }

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
	
	// TODO maybe "simple" isn't possible to determine outside the context of a scale!
	//bool isSimple() const;
	//Note getSimplified() const; // TODO implement e.g. E# -> F, Abb -> G. Return true if something changed
};

std::ostream& operator<<(std::ostream &os, const Note &note);

#endif // NOTE_H