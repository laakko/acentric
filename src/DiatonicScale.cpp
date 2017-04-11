#include "DiatonicScale.h"

DiatonicScale::DiatonicScale(Note base, std::vector<Interval> degrees)
{
	// Check input
	if (degrees.size() != 6)
		throw "bad degrees vector size in DiatonicScale ctor: " + std::to_string(degrees.size());
	for (int i = 0; i < degrees.size(); ++i) {
		// Make sure each basic note is used in the scale and is passed in proper order
		if (degrees.at(i).getBasicDistance() != i + 1)
			throw "improper ordering of basic intervals passed to DiatonicScale ctor";
		// Make sure each degree is properly ordered by number of semitones; ensure 7 distinct pitch classes are in the scale
		if (i > 0 && (degrees.at(i).getSemitones() <= degrees.at(i-1).getSemitones()) )
			throw "improper ordering of semitones passed to DiatonicScale ctor"; // TODO make better error messages
	}
	this->base = base;
	this->degrees = degrees;
}

DiatonicScale::DiatonicScale(Note base, BasicScale scale)
{
	this->base = base;
	
	//TODO should I delegate to the above constructor to validate the degree vectors generated here?
	//TODO alphabetical order, or musical order? right now it's somewhat alphabetical
	switch (scale) {
	case BasicScale::Aeolian:
	case BasicScale::Minor:
		degrees = Interval::makeIntervalVector("M2 m3 P4 P5 m6 m7");
		break;

	case BasicScale::Dorian:
		degrees = Interval::makeIntervalVector("M2 m3 P4 P5 M6 m7");
		break;

	case BasicScale::Ionian:
	case BasicScale::Major:
		degrees = Interval::makeIntervalVector("M2 M3 P4 P5 M6 M7");
		break;

	case BasicScale::Locrian:
		degrees = Interval::makeIntervalVector("m2 m3 P4 d5 m6 m7");
		break;

	case BasicScale::Lydian:
		degrees = Interval::makeIntervalVector("M2 M3 A4 P5 M6 M7");
		break;

	case BasicScale::Mixolydian:
		degrees = Interval::makeIntervalVector("M2 M3 P4 P5 M6 m7");
		break;

	case BasicScale::Phrygian:
		degrees = Interval::makeIntervalVector("m2 m3 P4 P5 m6 m7");
		break;
	}
}

std::vector<Note> DiatonicScale::getDegrees() const
{
	std::vector<Note> scaleNotes;
	for (auto &interval : this->degrees)
		scaleNotes.push_back(this->base.getOtherNote(interval));

	
	return scaleNotes;
}

std::ostream & operator<<(std::ostream & os, const DiatonicScale & scale)
{
	os << scale.getBase();
	for (auto &note : scale.getDegrees()) {
		os << " " << note; // TODO don't print octave (should be quick fix)
	}

	return os;
}
