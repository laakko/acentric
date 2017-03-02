// Note.h
#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <iostream>
#include "BasicNote.h"

class Note{

private:
	BasicNote base;
	int offset;
	int octave;

public:
	Note(BasicNote base = BasicNote::A, int offset = 0, int octave = 4);
	//Note(std::string textNote); // TODO implement

	//Note operator+(int semitones); // TODO implement (implicit simplify)
	//Note operator-(int semitones); // TODO implement (implicit simplify)

	BasicNote getBase() const { return base; }
	int getOffset() const { return offset; }
	int getOctave() const { return octave; }
	int getAbsoluteDistance() const;

	int baseToBaseDistance(BasicNote other, bool upper = true) const; // TODO delete? do I even need this?

	//bool simplify(); // TODO implement e.g. E# -> F, Abb -> G. Return true if something changed

};

std::ostream& operator<<(std::ostream &os, const Note &note);

#endif // NOTE_H