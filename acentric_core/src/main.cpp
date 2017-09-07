#include <iostream>
#include <string>
#include <vector>
#include "BasicNote.h"
#include "Note.h"
#include "Interval.h"
#include "DiatonicScale.h"
#include "BasicScale.h"
#include "Chord.h"
#include "BasicChord.h"

int main() {
	using namespace acentric_core;

	DiatonicScale csLocrian{ Note{'A'}, BasicScale::Locrian };
	std::cout << csLocrian << std::endl;

	Chord dsMaj{ Note{'D', 1}, BasicChord::maj };
	std::cout << dsMaj << std::endl;

	std::vector<Interval> chordSuffix;
	chordSuffix.push_back(Interval{ 'm', 3 });
	chordSuffix.push_back(Interval{ 'P', 5 });

	// std::cout << chordSuffix << std::endl; // won't compile, std::vector has no in-built operator<<

	int i;
	std::cin >> i;
    exit(0);
}