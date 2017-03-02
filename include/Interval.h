// Interval.h
#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {

private:
	int basicNotesEncompassed;
	int semitonesFromBase; // if negative, this is a lower interval

public:
	Interval(int basicNotesEncompassed = 1, int semitonesFromBase = 0);
	//Interval(std::string commonName, bool upper = true); // TODO implement

};

#endif // INTERVAL_H