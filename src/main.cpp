#include <iostream>
#include <string>
#include "BasicNote.h"
#include "Note.h"

int main() {
	std::cout << "Test\n";

	try {
		Note testNote{ BasicNote::A, 0, 4 };
		Note badNote{ BasicNote::F, -3, 5 };
	}
	catch (const std::string& exception) {
		std::cout << "Error: " << exception;
	}


	int i;
	std::cin >> i;
    exit(0);
}