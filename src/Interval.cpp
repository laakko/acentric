#include "Interval.h"

Interval::Interval(int basicInterval, int semitones)
{
	if (basicInterval < 1)
		throw "bad basicInterval parameter in Interval ctor: " + std::to_string(basicInterval);
	this->basicInterval = basicInterval;

	if (semitones < 0)
		throw "bad semitones parameter in Interval ctor: " + std::to_string(semitones);
	this->semitones = semitones;
}

Interval::Interval(const Note &firstNote, const Note &secondNote)
{
	basicInterval = firstNote.getBasicDistance(secondNote) + 1; // offset required since intervals count the starting note as 1, not 0
	semitones = firstNote.getRelativeDistance(secondNote);
}
