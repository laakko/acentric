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

int Note::getAbsoluteDistance() const
{
	int distance{ 0 };
	distance += octave * 12;
	distance += offset;

	switch (static_cast<int>(base)) {
	case 0: // A
		break; // A is already 0
	case 1: // B
		distance += 2;
		break;
	case 2: // C
		distance += 3;
		break;
	case 3: // D
		distance += 5;
		break;
	case 4: // E
		distance += 7;
		break;
	case 5: // F
		distance += 8;
		break;
	case 6: // G
		distance += 10;
		break;
	}
	return distance;
}

int Note::baseToBaseDistance(BasicNote other, bool upper) const
{
	int thisBase{ static_cast<int>(base) };
	int otherBase{ static_cast<int>(other) };
	int distance{ 0 };

	while (thisBase != otherBase) {
		if (upper) {
			// Count upward mod 7
			if (thisBase == 1 || thisBase == 4) {
				// B->C or E->F
				distance += 1;
			}
			else {
				distance += 2;
			}
			thisBase = (thisBase + 1) % 7;
		}
		else {
			// Count downward mod 7
			if (thisBase == 2 || thisBase == 5) {
				// C->B or F->E
				distance += 1;
			}
			else {
				distance += 2;
			}
			// Can't use % here, since % isn't a euclidian mod!
			if (thisBase == 0)
				thisBase = 6;
			else --thisBase;
		}
	}

	return distance;
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
	// TODO rewrite to allow more flexibility
	// e.g. if offset is -7 print (b^7)
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
