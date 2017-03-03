#include <iostream>
#include <string>
#include "BasicNote.h"
#include "Note.h"

int main() {
	std::cout << "Test\n";

	Note testNote = Note::Note(BasicNote::A, 0, 4 );
	Note badNote = Note::Note(BasicNote::F, -3, 5);

	std::cout << badNote << std::endl;

	int i;
	std::cin >> i;
    exit(0);
}