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
	
	switch (scale) {
	case BasicScale::Aeolian:
		degrees.push_back(Interval::Interval("M2"));
		degrees.push_back(Interval::Interval("m3"));
		degrees.push_back(Interval::Interval("P4"));
		degrees.push_back(Interval::Interval("P5"));
		degrees.push_back(Interval::Interval("m6"));
		degrees.push_back(Interval::Interval("m7"));
		break;

	case BasicScale::Dorian:
		// TODO finish adding scales, but use Interval::makeIntervalVector instead
		// This will also be useful for chords later on
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
