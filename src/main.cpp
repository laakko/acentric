#include <iostream>
#include <string>
#include <vector>
#include "BasicNote.h"
#include "Note.h"
#include "Interval.h"
#include "DiatonicScale.h"
#include "BasicScale.h"

int main() {
	//Note scaleBase{ Note::Note("Bb") };
	//std::vector<Interval> degrees;
	//degrees.push_back(Interval::Interval(1, 2));
	//degrees.push_back(Interval::Interval(2, 4));
	//degrees.push_back(Interval::Interval(3, 5));
	//degrees.push_back(Interval::Interval(4, 7));
	//degrees.push_back(Interval::Interval(5, 9));
	//degrees.push_back(Interval::Interval(6, 11));

	//DiatonicScale cMajor{ scaleBase, degrees };

	//std::cout << cMajor << std::endl;

	/*Note wut{ "C4" };
	Interval wha{ "A13" };
	std::cout << wut + wha << std::endl;*/

	DiatonicScale csLocrian{ Note::Note("C#"), BasicScale::Locrian };
	std::cout << csLocrian << std::endl;

	//Interval::makeIntervalVector("m2, M3 P4...P5");

	int i;
	std::cin >> i;
    exit(0);
}