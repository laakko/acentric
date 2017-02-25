// Note.h
#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <map>

class Note{

private:
	int pitch{ 40 }; // Valid range 1-88; default Middle-C

public:
	Note(std::string human_name);
	Note(int pitch);
	// TODO overload <<

	static const std::map<std::string, int> s_note;
};

#endif // NOTE_H