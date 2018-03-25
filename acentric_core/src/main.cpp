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
#include "CounterpointChecker.h"

using namespace acentric_core;

void printVec(std::vector<Note>& notes) {
	for (auto note : notes) {
		std::cout << note << "\t";
	}
	std::cout << std::endl;
}

int main() {

	std::vector<Note> cf;
	std::vector<Note> cp;

	cf.push_back(Note{ BasicNote::C });
	cf.push_back(Note{ BasicNote::D });
	cf.push_back(Note{ BasicNote::E });
	cf.push_back(Note{ BasicNote::F });
	cf.push_back(Note{ BasicNote::G });
	cf.push_back(Note{ BasicNote::A, 0, 5 });
	cf.push_back(Note{ BasicNote::B, 0, 5 });
	cf.push_back(Note{ BasicNote::C, 0, 5 });

	cp.push_back(Note{ BasicNote::C });
	cp.push_back(Note{ BasicNote::D });
	cp.push_back(Note{ BasicNote::E });
	cp.push_back(Note{ BasicNote::F });
	cp.push_back(Note{ BasicNote::G });
	cp.push_back(Note{ BasicNote::A, 0, 5 });
	cp.push_back(Note{ BasicNote::B, 0, 5 });
	cp.push_back(Note{ BasicNote::C, 0, 5 });

	printVec(cf);
	printVec(cp);

	auto cpc = CounterpointChecker(cf, cp);
	if (cpc.counterpointIsValid()) {
		std::cout << "Counterpoint is valid\n";
	}
	else {
		std::cout << "Counterpoint is not valid\n";
	}

	int i;
	std::cin >> i;
    exit(0);
}