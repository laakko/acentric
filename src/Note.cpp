#include "Note.h"
#include "BasicNote.h"

Note::Note(BasicNote base, int offset, int octave)
{
	// TODO validate input
	this->base = base;
	if (offset < -2 || offset > 2)
		throw "bad offset given to Note constructor: " + std::to_string(offset);
	this->offset = offset;
	this->octave = octave;
}

std::ostream& operator<<(std::ostream &os, const Note &note)
{
	// Print base note
	switch (note.getBase()) {
	case BasicNote::A:
		os << "A";
		break;
	case BasicNote::B:
		os << "B";
		break;
	case BasicNote::C:
		os << "C";
		break;
	case BasicNote::D:
		os << "D";
		break;
	case BasicNote::E:
		os << "E";
		break;
	case BasicNote::F:
		os << "F";
		break;
	case BasicNote::G:
		os << "G";
		break;
	}

	// Print sharps or flats
	switch (note.getOffset()) {
	case -2:
		os << "bb";
		break;
	case -1:
		os << "b";
		break;
	case 1:
		os << "#";
		break;
	case 2:
		os << "##"; // TODO which is better...## or x?
		break;
	}

	// Print octave
	os << note.getOctave();

	return os;
}
