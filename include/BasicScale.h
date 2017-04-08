// BasicScale.h
#ifndef BASICSCALE_H
#define BASICSCALE_H

enum class BasicScale {
	Chromatic,
	Major,
	Minor, // i.e. natural minor
	// MelodicMinor, // TODO figure out how to deal with this one
	HarmonicMinor,
	Ionian, // same as Major
	Dorian,
	Phrygian,
	Lydian,
	Mixolydian,
	Aeolian, // same as Minor
	Locrian
};

#endif // BASICSCALE_H