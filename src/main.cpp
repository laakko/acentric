#include <iostream>
#include <string>
#include <vector>
#include "BasicNote.h"
#include "Note.h"
#include "Interval.h"
#include "DiatonicScale.h"

int main() {
	Note scaleBase{ BasicNote::A, -1, 4 };
	std::vector<Interval> degrees;
	degrees.push_back(Interval::Interval(1, 2));
	degrees.push_back(Interval::Interval(2, 4));
	degrees.push_back(Interval::Interval(3, 5));
	degrees.push_back(Interval::Interval(4, 7));
	degrees.push_back(Interval::Interval(5, 9));
	degrees.push_back(Interval::Interval(6, 11));

	DiatonicScale cMajor{ scaleBase, degrees };

	std::cout << cMajor;

	int i;
	std::cin >> i;
    exit(0);
}