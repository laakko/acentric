#include <iostream>
#include <string>
#include "BasicNote.h"
#include "Note.h"

int main() {
	std::cout << "Test\n";

	Note testNote;
	Note badNote;
	try {
		testNote = Note::Note(BasicNote::A, 0, 4 );
		badNote = Note::Note(BasicNote::F, -3, 5);
	}
	catch (const std::string &exception) {
		std::cout << "Error: " << exception << std::endl;
	}

	std::cout << testNote << std::endl;

	Note testNote2{ BasicNote::F, 2, 3 };
	std::cout << testNote2 << std::endl;

	int i;
	std::cin >> i;
    exit(0);
}