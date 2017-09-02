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

	int i;
	std::cin >> i;
    exit(0);
}