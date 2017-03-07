#include <iostream>
#include <string>
#include "BasicNote.h"
#include "Note.h"
#include "Interval.h"

int main() {
	/*Interval interOne{ 2, 4 };
	Note noteOne{ BasicNote::C, 0, 4 };
	Note calculated{ noteOne + interOne };
	Note calculated2{ noteOne - interOne };
	std::cout << noteOne << " with added interval " << interOne << " is " << calculated << std::endl;
	std::cout << noteOne << " with subtracted interval " << interOne << " is " << calculated2 << std::endl;*/

	Note noteTwo{ BasicNote::A, -2, 6 };
	std::cout << noteTwo.isSimple() << std::endl;

	int i;
	std::cin >> i;
    exit(0);
}