// Note.h
#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <map>
#include "Key.h"

class Note{

private:
	int pianoKeyNum{ 40 }; // Valid range 1-88; default Middle-C
	Key key{ Key::C };

	int octave();
	std::string name();

public:
	Note(std::string humanName, Key = Key::C);
	Note(int pianoKeyNum, Key = Key::C);
	// TODO overload <<

	static const std::map<std::string, int> s_note;
};

#endif // NOTE_H