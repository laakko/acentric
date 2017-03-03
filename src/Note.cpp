#include "Note.h"
#include "BasicNote.h"

Note::Note(BasicNote base, int offset, int octave)
{
	// TODO validate input
	this->base = base;
	this->offset = offset;
	this->octave = octave;
}

int Note::getAbsoluteDistance() const
{
	int distance{ 0 };
	distance += octave * 12;
	distance += offset;

	// TODO rewrite without cast?
	switch (static_cast<int>(base)) {
	case 0: // A
		break; // no need to add anything
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

int Note::getBasicDistance(const Note &other) const
{
	int thisBase = static_cast<int>(base);
	int otherBase = static_cast<int>(other.getBase());
	int thisOctave = octave;
	int otherOctave = other.getOctave();

	int lowBase;
	int lowOctave;
	int highBase;
	int highOctave;

	if ((thisOctave < otherOctave) || 
		(thisOctave == otherOctave && thisBase < otherBase)) {
		// This name/octave is lower
		lowBase = thisBase;
		lowOctave = thisOctave;
		highBase = otherBase;
		highOctave = otherOctave;
	}
	else if (thisOctave == otherOctave && thisBase == otherBase) {
		// Both names/octaves are the same
		return 0;
	} else if ((thisOctave == otherOctave && thisBase > otherBase) ||
		(thisOctave > otherOctave)) {
		// This name/octave is higher
		lowBase = otherBase;
		lowOctave = otherOctave;
		highBase = thisBase;
		highOctave = thisOctave;
	}

	return ((highOctave - lowOctave) * 7) + (highBase - lowBase);
}

int Note::getRelativeDistance(const Note &other) const
{
	int thisDistance{ getAbsoluteDistance() };
	int otherDistance{ other.getAbsoluteDistance() };
	
	if (thisDistance > otherDistance)
		return thisDistance - otherDistance;
	else
		return otherDistance - thisDistance;
}

Note Note::getOtherNote(const Interval &interval, bool getHigherNote) const
{
	// TODO don't forget lower option!
	int otherOctave{ octave };
	int otherBase{ static_cast<int>(base) };
	int otherOffset{ offset };

	otherOctave += ((interval.getBasicInterval() - 1) / 7);
	otherBase += ((interval.getBasicInterval() - 1) % 7);

	otherOctave += otherBase / 7;
	otherBase %= 7;

	Note intermediate{ static_cast<BasicNote>(otherBase), 0, otherOctave };
	otherOffset = getAbsoluteDistance() + interval.getSemitones() - intermediate.getAbsoluteDistance();

	return Note(static_cast<BasicNote>(otherBase), otherOffset, otherOctave); // TODO test, test, test!
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
