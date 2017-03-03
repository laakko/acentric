#include "Interval.h"

Interval::Interval(int basicDistance, int semitones)
{
	if (basicDistance < 0)
		throw "bad basicDistance parameter in Interval ctor: " + std::to_string(basicDistance);
	this->basicDistance = basicDistance;

	if (semitones < 0)
		throw "bad semitones parameter in Interval ctor: " + std::to_string(semitones);
	this->semitones = semitones;
}

std::ostream & operator<<(std::ostream & os, const Interval & interval)
{
	// Determine if the interval, unmodified, would be P or M
	bool perfect{ false };
	int basicDistance{ interval.getbasicDistance() };

	if (basicDistance % 7 == 0 || basicDistance % 7 == 3 || basicDistance % 7 == 4)
		perfect = true;
	else
		perfect = false; // so it would be Major instead

	// Find how many semitones the P/M interval would have
	int naturalSemitones{ (basicDistance / 7) * 12 };
	switch (basicDistance % 7) {
	case 0:
		break;
	case 1:
		naturalSemitones += 2;
		break;
	case 2:
		naturalSemitones += 4;
		break;
	case 3:
		naturalSemitones += 5;
		break;
	case 4:
		naturalSemitones += 7;
		break;
	case 5:
		naturalSemitones += 9;
		break;
	case 6:
		naturalSemitones += 11;
		break;
	}

	int offset{ interval.getSemitones() - naturalSemitones };

	if ((offset < -2) || (offset == -2 && perfect))
		os << "(b^" << offset << ")"; // TODO print P or M before the b
	else if ((offset == -2 && !perfect) || (offset == -1 && perfect))
		os << "d";
	else if (offset == -1 && !perfect)
		os << "m";
	else if (offset == 0 && perfect)
		os << "P";
	else if (offset == 0 && !perfect)
		os << "M";
	else if (offset == 1)
		os << "A";
	else if (offset > 1)
		os << "(#^" << offset << ")"; // TODO print P or M before the #

	os << basicDistance + 1;

	return os;
}
