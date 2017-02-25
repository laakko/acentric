#include <iostream>
#include <map>
#include "Note.h"

int main(){
    std::cout << "Test\n";

	std::cout << Note::s_note.at("A0") << std::endl << 
		Note::s_note.at("C#4") << std::endl << 
		Note::s_note.at("Db4") << std::endl;

	Note n{ "C#4" };

	int i;
	std::cin >> i;
    exit(0);
}