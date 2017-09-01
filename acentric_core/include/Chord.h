// Chord.h
#ifndef CHORD_H
#define CHORD_H

#include <iostream>
#include <vector>

#include "Note.h"
#include "Interval.h"
#include "BasicChord.h"

namespace acentric_core {

	class Chord {

	private:
		Note root;
		std::vector<Interval> pitches;

	public:
		Chord(Note root, BasicChord chord);
		Chord(Note root, std::vector<Interval> pitches);

		Note getBase() const { return root; }
		std::vector<Interval> getPitches() const { return pitches; }

		void insertPitch(Interval pitchToInsert);
		void removePitch(Interval pitchToRemove);
		void setRoot(Note newRoot);

		// TODO add functionality to get inversions

	};

	std::ostream& operator<<(std::ostream &os, const Chord &chord);

}

#endif // CHORD_H