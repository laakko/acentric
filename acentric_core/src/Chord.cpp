#include "Chord.h"

namespace acentric_core {

	Chord::Chord(Note root, BasicChord chord) :
		root(root)
	{
		switch (chord) {
		case BasicChord::maj:
			pitches.push_back(Interval{ 'M', 3 });
			pitches.push_back(Interval{ 'P', 5 });
			break;

		case BasicChord::min:
			pitches.push_back(Interval{ 'm', 3 });
			pitches.push_back(Interval{ 'P', 5 });
			break;

		case BasicChord::aug:
			pitches.push_back(Interval{ 'M', 3 });
			pitches.push_back(Interval{ 'a', 5 });
			break;

		case BasicChord::dim:
			pitches.push_back(Interval{ 'm', 3 });
			pitches.push_back(Interval{ 'd', 5 });
			break;

		case BasicChord::maj6:
			pitches.push_back(Interval{ 'M', 3 });
			pitches.push_back(Interval{ 'P', 5 });
			pitches.push_back(Interval{ 'M', 6 });
			break;

		case BasicChord::min6:
			pitches.push_back(Interval{ 'm', 3 });
			pitches.push_back(Interval{ 'P', 5 });
			pitches.push_back(Interval{ 'M', 6 });
			break;

		case BasicChord::dom7:
			pitches.push_back(Interval{ 'M', 3 });
			pitches.push_back(Interval{ 'P', 5 });
			pitches.push_back(Interval{ 'm', 7 });
			break;

		case BasicChord::maj7:
			pitches.push_back(Interval{ 'M', 3 });
			pitches.push_back(Interval{ 'P', 5 });
			pitches.push_back(Interval{ 'M', 7 });
			break;

		case BasicChord::min7:
			pitches.push_back(Interval{ 'm', 3 });
			pitches.push_back(Interval{ 'P', 5 });
			pitches.push_back(Interval{ 'm', 7 });
			break;

		case BasicChord::aug7:
			pitches.push_back(Interval{ 'M', 3 });
			pitches.push_back(Interval{ 'a', 5 });
			pitches.push_back(Interval{ 'm', 7 });
			break;

		case BasicChord::dim7:
			pitches.push_back(Interval{ 'm', 3 });
			pitches.push_back(Interval{ 'd', 5 });
			pitches.push_back(Interval{ 'd', 7 });
			break;

		case BasicChord::halfdim7:
			pitches.push_back(Interval{ 'm', 3 });
			pitches.push_back(Interval{ 'd', 5 });
			pitches.push_back(Interval{ 'm', 7 });
			break;

		case BasicChord::min_maj7:
			pitches.push_back(Interval{ 'm', 3 });
			pitches.push_back(Interval{ 'P', 5 });
			pitches.push_back(Interval{ 'M', 7 });
			break;

		}
	}

	Chord::Chord(Note root, std::vector<Interval> pitches) : // TODO test
		root(root)
	{
		// Validate given pitches; they should be in strictly increasing order from the root (no duplicates)
		if (pitches.size() == 0) throw std::invalid_argument("Attempted to create a Chord with no non-root pitches");

		int prevDistance = pitches.at(0).getBasicDistance();
		if (prevDistance == 0) throw std::invalid_argument("Attempted to create a Chord with a P1 or d2 pitch (duplicates root note)"); // TODO confusing error message, fix

		for (int i = 1; i < pitches.size(); ++i) {
			if (!(pitches.at(i).getBasicDistance() > prevDistance)) throw std::invalid_argument("Attempted to create a chord with non-increasing pitches"); // TODO maybe try sorting?
			prevDistance = pitches.at(i).getBasicDistance(); // TODO also need to compare semitone distance, not just basic distance!
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
