#include "Chord.h"

Chord::Chord(Note root, BasicChord chord) :
	root(root)
{
	switch (chord) {
	case BasicChord::maj:
		pitches = Interval::makeIntervalVector("M3 P5");
		break;

	case BasicChord::min:
		pitches = Interval::makeIntervalVector("m3 P5");
		break;

	case BasicChord::aug:
		pitches = Interval::makeIntervalVector("M3 A5");
		break;

	case BasicChord::dim:
		pitches = Interval::makeIntervalVector("m3 d5");
		break;

	case BasicChord::maj6:
		pitches = Interval::makeIntervalVector("M3 P5 M6");
		break;

	case BasicChord::min6:
		pitches = Interval::makeIntervalVector("m3 P5 M6");
		break;

	case BasicChord::dom7:
		pitches = Interval::makeIntervalVector("M3 P5 m7");
		break;

	case BasicChord::maj7:
		pitches = Interval::makeIntervalVector("M3 P5 M7");
		break;

	case BasicChord::min7:
		pitches = Interval::makeIntervalVector("m3 P5 m7");
		break;

	case BasicChord::aug7:
		pitches = Interval::makeIntervalVector("M3 A5 m7");
		break;

	case BasicChord::dim7:
		pitches = Interval::makeIntervalVector("m3 d5 d7");
		break;

	case BasicChord::halfdim7:
		pitches = Interval::makeIntervalVector("m3 d5 m7");
		break;

	case BasicChord::min_maj7:
		pitches = Interval::makeIntervalVector("m3 P5 M7");
		break;

	}
}

Chord::Chord(Note root, std::vector<Interval> pitches)
{
}

void Chord::setRoot(Note newRoot)
{
	this->root = newRoot;
}

std::ostream & operator<<(std::ostream & os, const Chord & chord)
{
	Note base = chord.getBase();
	std::vector<Interval> pitches = chord.getPitches();
	os << "(" << base;

	for (auto pitch : pitches) {
		os << " " << (base + pitch);
	}
	os << ")";
	return os;
}
