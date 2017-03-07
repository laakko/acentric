// Interval.h
#ifndef INTERVAL_H
#define INTERVAL_H

#include <iostream>
#include <string>

class Interval {

private:
	int basicDistance; // e.g. basic distance from C#4-Eb4 is 2
	int semitones;

public:
	// basicDistance == basicInterval - 1
	// Musical notation uses a 1 to refer to "self".
	// Distance uses a 0 to refer to "self".
	// Consequently, input to the ctor is off by one.
	// I.e. Interval(3, 4) would generate d4, *not* M3.
	Interval(int basicDistance = 0, int semitones = 0);
	//Interval(std::string commonName); // TODO implement

	//Interval getInversion() const; // TODO implement
	int getBasicInterval() const { return basicDistance + 1; }
	int getBasicDistance() const { return basicDistance; }
	int getSemitones() const { return semitones; }

	// TODO add chromatic intervals, e.g. C4-F4 = i5
};

std::ostream& operator<<(std::ostream &os, const Interval &interval);

#endif // INTERVAL_H