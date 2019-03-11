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



	std::cout << "A dorian scale: " <<  DiatonicScale(Note {BasicNote::A}, BasicScale {BasicScale::Major}) << std::endl;

	std::cout << Chord(Note {BasicNote::C}, BasicChord {BasicChord::min}) << std::endl;


}