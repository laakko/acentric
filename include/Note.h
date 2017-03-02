// Note.h
#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <iostream>
#include "BasicNote.h"

class Note{

private:
	BasicNote base;
	int offset; // -2, -1, 0, 1, or 2 (semitones)
	int octave;

public:
	Note(BasicNote base = BasicNote::A, int offset = 0, int octave = 4);
	//Note(std::string textNote); // TODO implement

	//Note operator+(int semitones); // TODO implement (minimize sharps/flats)
	//Note operator-(int semitones); // TODO implement (minimize sharps/flats)

	BasicNote getBase() const { return base; }
	int getOffset() const { return offset; }
	int getOctave() const { return octave; }

};

std::ostream& operator<<(std::ostream &os, const Note &note);

#endif // NOTE_H