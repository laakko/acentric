// Interval.h
#ifndef INTERVAL_H
#define INTERVAL_H

#include "Note.h"
class Note;

class Interval {

private:
	int basicInterval; // e.g. interval from C4-E4 is 3
	int semitones;

public:
	Interval(int basicInterval = 1, int semitones = 0);
	//Interval(std::string commonName); // TODO implement

	int getBasicInterval() const { return basicInterval; }
	int getSemitones() const { return semitones; }
};

//std::ostream& operator<<(std::ostream &os, const Interval &interval); // TODO implement

#endif // INTERVAL_H