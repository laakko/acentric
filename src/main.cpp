#include <iostream>
#include <string>
#include "BasicNote.h"
#include "Note.h"
#include "Interval.h"

int main() {
	Note testNote = Note::Note(BasicNote::A, 0, 4 );
	Note badNote = Note::Note(BasicNote::F, -3, 5);

	Note first{ BasicNote::C, 0, 4 };
	Note second{ BasicNote::G, -2, 6 };

	Interval myInterval = first.getInterval(second);

	std::cout << "Interval: " << myInterval << std::endl;

	int i;
	std::cin >> i;
    exit(0);
}