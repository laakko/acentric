// DiatonicScale.h
#ifndef DIATONIC_SCALE_H
#define DIATONIC_SCALE_H

#include <vector>
#include "BasicScale.h"
#include "Note.h"
#include "Interval.h"

class DiatonicScale {

private:
	Note base;
	std::vector<Interval> degrees;
	//bool properOrder(std::vector<Interval> degrees); // TODO should I use this to validate BasicScale-based ctor strings?

public:
	// The degrees vector must include six Intervals in strictly increasing order, with distances 1-6 (i.e. basic intervals 2-7)
	// and the semitone counts must also be strictly increasing
	// It is assumed the base is the first degree of the scale (but this doesn't allow, e.g., an A1 in any scale...is that a problem?)
	// TODO explain/document this better
	DiatonicScale(Note base, std::vector<Interval> degrees);
	DiatonicScale(Note base, std::vector<Note> degrees); // ignore octave designation
	DiatonicScale(Note base, BasicScale scale); // TODO finish implementing, dangerous to use right now
	std::vector<Note> getDegrees() const;

	Note getBase() const { return base; };

	// TODO ...do I even need these functions? how robust do I want this library to be?
	//DiatonicScale getRelative() const;
	//DiatonicScale getParallel() const;
	
	bool isInScale(Note &note) const;
	Note simplify(Note &note) const;

};

std::ostream& operator<<(std::ostream &os, const DiatonicScale &scale);

#endif //DIATONIC_SCALE_H