// Chord.h
#ifndef CHORD_H
#define CHORD_H

#include <iostream>
#include <vector>

#include "Note.h"
#include "Interval.h"
#include "BasicChord.h"

class Chord {

private:
	BasicNote base;
	std::vector<Interval> degrees; // TODO rename...maybe "pitches"?

public:
	Chord(BasicNote base, BasicChord chord);
	Chord(BasicNote base, std::vector<Interval> degrees);

	void insertPitch(Interval pitchToInsert);
	void setBase(Note newBase);

};

#endif // CHORD_H