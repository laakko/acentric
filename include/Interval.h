// Interval.h
#ifndef INTERVAL_H
#define INTERVAL_H

#include "Note.h"
class Note;

class Interval {

private:
	int basicDistance; // e.g. distance from C4-E4 is 2
	int semitones;

public:
	Interval(int basicDistance = 0, int semitones = 0);
	//Interval(std::string commonName); // TODO implement

	int getbasicDistance() const { return basicDistance; }
	int getSemitones() const { return semitones; }
};

std::ostream& operator<<(std::ostream &os, const Interval &interval);

#endif // INTERVAL_H