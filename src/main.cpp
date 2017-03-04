#include <iostream>
#include <string>
#include "BasicNote.h"
#include "Note.h"
#include "Interval.h"

int main() {
	Interval interOne{ 13, 22 };
	Note noteOne{ BasicNote::D, 2, 0 };
	Note calculated{ noteOne.getOtherNote(interOne, true) };
	std::cout << "Lower other note of " << noteOne << " with interval " << interOne << " is " << calculated << std::endl;

	int i;
	std::cin >> i;
    exit(0);
}