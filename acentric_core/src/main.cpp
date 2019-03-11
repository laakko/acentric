#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "BasicNote.h"
#include "Note.h"
#include "Interval.h"
#include "Scale.h"
#include "BasicScale.h"
#include "Chord.h"
#include "BasicChord.h"
#include "CounterpointChecker.h"

using namespace acentric_core;

void printVec(std::vector<Note>& notes) {
	for (auto note : notes) {
		std::cout << note << "\t";
	}
	std::cout << std::endl;
}

int main() {



	std::cout << "A dorian scale: " <<  Scale(Note {BasicNote::A}, BasicScale {BasicScale::Dorian}) << std::endl;
	std::cout << "E minor scale: " <<  Scale(Note {BasicNote::E}, BasicScale {BasicScale::Minor}) << std::endl;
	std::cout << "E minor pentatonic scale: " <<  Scale(Note {BasicNote::E}, BasicScale {BasicScale::MinorPentatonic}) << std::endl;
	std::cout << "C blues scale: " <<  Scale(Note {BasicNote::C}, BasicScale {BasicScale::Blues}) << std::endl;
	std::cout << "E Metallica scale: " <<  Scale(Note {BasicNote::E}, BasicScale {BasicScale::Metallica}) << std::endl;



	std::cout << Chord(Note {BasicNote::C}, BasicChord {BasicChord::min}) << std::endl;


}