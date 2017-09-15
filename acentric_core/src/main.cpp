#include <iostream>
#include <algorithm>
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

	std::vector<Interval> chordSuffix;
	//chordSuffix.push_back(Interval{ 'P', 1 });
	chordSuffix.push_back(Interval{ 'a', 3 });
	chordSuffix.push_back(Interval{ 'a', 3 });
	//chordSuffix.push_back(Interval{ 'a', 2 });
	chordSuffix.push_back(Interval{ 'P', 5 });
	chordSuffix.push_back(Interval{ 'm', 2 });
	chordSuffix.push_back(Interval{ 'm', 2 });
	chordSuffix.push_back(Interval{ 'm', 2 });

	try {
		Chord myChord{ Note{ 'A' }, chordSuffix };
		std::cout << myChord;
	}
	catch (std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
	}




	int i;
	std::cin >> i;
    exit(0);
}