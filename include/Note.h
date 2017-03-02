// Note.h
#ifndef NOTE_H
#define NOTE_H

#include <string>
#include "BasicNote.h"

class Note{

private:
	BasicNote base;
	int offset; // -2, -1, 0, 1, or 2 (semitones)
	int octave;

public:
	Note(BasicNote base = BasicNote::C, int offset = 0, int octave = 4);
	Note(std::string textNote = "C4");
	
};

#endif // NOTE_H