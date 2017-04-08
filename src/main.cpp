#include <iostream>
#include <string>
#include <vector>
#include "BasicNote.h"
#include "Note.h"
#include "Interval.h"
#include "DiatonicScale.h"

int main() {
	/*Note scaleBase{ BasicNote::C, 0, 4 };
	std::vector<Interval> degrees;
	degrees.push_back(Interval::Interval(1, 2));
	degrees.push_back(Interval::Interval(2, 3));
	degrees.push_back(Interval::Interval(3, 5));
	degrees.push_back(Interval::Interval(4, 7));
	degrees.push_back(Interval::Interval(5, 8));
	degrees.push_back(Interval::Interval(6, 10));

	DiatonicScale cMajor{ scaleBase, degrees };

	std::cout << cMajor;*/

	//std::cout << Note::Note(BasicNote::A, -5, -4) << std::endl;
	Note hmm{ "A####-5" };
	std::cout << hmm << std::endl;

	int i;
	std::cin >> i;
    exit(0);
}