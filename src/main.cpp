#include <iostream>
#include <string>
#include "BasicNote.h"
#include "Note.h"

int main() {
	std::cout << "Test\n";

	Note testNote = Note::Note(BasicNote::A, 0, 4 );
	Note badNote = Note::Note(BasicNote::F, -3, 5);

	std::cout << testNote << std::endl;

	Note testNote2{ BasicNote::F, 2, -3 };
	Note testNote3{ BasicNote::D, 0, 5 };
	Note testNote4{ BasicNote::B, 2, 4 };
	Note testNote5{ BasicNote::C, 1, 4 };

	std::cout << testNote4.getBasicDistance(testNote2) << std::endl;

	int i;
	std::cin >> i;
    exit(0);
}