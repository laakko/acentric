#include "Chord.h"

namespace acentric_core {

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

	Chord::Chord(Note root, std::vector<Interval> pitches) : // TODO test
		root(root)
	{
		// Validate given pitches; they should be in strictly increasing order from the root (no duplicates)
		if (pitches.size() == 0) throw "Empty Interval vector passed to Chord ctor";

		int prevDistance = pitches.at(0).getBasicDistance();
		if (prevDistance == 0) throw "P1 or d2 in Interval vector passed to Chord ctor (duplicates root note)";

		for (int i = 1; i < pitches.size(); ++i) {
			if (!(pitches.at(i).getBasicDistance() > prevDistance)) throw "Non-increasing Interval vector passed to Chord ctor";
			prevDistance = pitches.at(i).getBasicDistance();
		}
		this->pitches = pitches;
	}

	void Chord::insertPitch(Interval pitchToInsert) // TODO implement
	{
		//for (int i = 0; i < pitches.size(); ++i) {
		//	if (pitchToInsert.getBasicDistance() < pitches.at(i).getBasicDistance()) {
		//		continue;
		//	}
		//	else if (pitchToInsert.getBasicDistance() == pitches.at(i).getBasicDistance()) {
		//		throw "Attempted to insert duplicate pitch into a Chord"; // TODO maybe just fail silently instead of throwing?
		//	}
		//	else if (pitchToInsert.getBasicDistance() > pitches.at(i).getBasicDistance()){
		//		pitches.insert(pitchToInsert);
		//	}
		//}
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

}
