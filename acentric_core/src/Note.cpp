#include <cmath>
#include <regex>
#include "Note.h"
#include "BasicNote.h"

Note::Note(BasicNote base, int offset, int octave) :
	base(base),
	offset(offset),
	octave(octave)
{
}

Note::Note(char base, int offset, int octave) :
	offset(offset),
	octave(octave)
{
	switch (base){
		case 'A':
			this->base = BasicNote::A;
			break;
		case 'B':
			this->base = BasicNote::B;
			break;
		case 'C':
			this->base = BasicNote::C;
			break;
		case 'D':
			this->base = BasicNote::D;
			break;
		case 'E':
			this->base = BasicNote::E;
			break;
		case 'F':
			this->base = BasicNote::F;
			break;
		case 'G':
			this->base = BasicNote::G;
			break;
		default:
			throw "Invalid base char passed to note ctor";
	}
}

Note::Note(const std::string & textNote)
{
	// Validate input; this allows e.g. C####, A(b^0) even though these forms are never printed out
	std::regex validNote{ R"REGEX(^[ABCDEFG]([#b]*|\([b#]\^[0-9]+\))?((-[0-9]+)|[0-9]*)$)REGEX" };
	
	if (!std::regex_match(textNote, validNote)) {
		throw "Invalid string passed to Note ctor";
	}

	// defaults, which will get overwritten based on input
	this->base = BasicNote::A;
	this->offset = 0;
	this->octave = 4;

	// character A -> number 65 -> number 0 -> BasicNote::A
	// TODO there's probably a better, less hackish way to do this
	this->base = static_cast<BasicNote>(static_cast<int>(textNote[0]) - 65);
	if (textNote.size() == 1)
		return;

	// TODO finish parsing
	std::regex numbers{ "-?[0-9]+" };
	if (std::regex_match(textNote.substr(1), numbers)) {
		// Found numbers representing an octave
		this->octave = std::stoi(textNote.substr(1));
	}
	else if (textNote[1] == '#' || textNote[1] == 'b') {
		// Found offset with #s and/or bs
		// Adjust offset until no #s and bs are left
		int i = 1;
		while (textNote[i] == '#' || textNote[i] == 'b') {
			if (textNote[i] == '#')
				++this->offset;
			if (textNote[i] == 'b')
				--this->offset;
			++i;
		}
		// #s and bs are parsed; finish by getting the octave, if applicable
		// TODO set to 4 by default
		if (textNote.size() > i)
			this->octave = std::stoi(textNote.substr(i));
	}
	else if (textNote[1] == '(') {
		// Found offset with parenthesis notation
		int endParen = textNote.find(')');
		int offset = std::stoi(textNote.substr(4, endParen - 4));
		if (textNote[2] == '#')
			this->offset = offset;
		if (textNote[2] == 'b')
			this->offset = -offset;

		// Get octave
		// TODO set to 4 by default
		if (textNote.size() > endParen + 1)
			this->octave = std::stoi(textNote.substr(endParen + 1));
	}


}

Note Note::operator+(Interval interval) const
{
	return getOtherNote(interval);
}

Note Note::operator-(Interval interval) const
{
	return getOtherNote(interval, true);
}

int Note::getAbsoluteDistance() const
{
	int distance{ 0 };
	distance += octave * 12;
	distance += offset;

	switch (base) {
	case BasicNote::A:
		break; // no need to add anything
	case BasicNote::B:
		distance += 2;
		break;
	case BasicNote::C:
		distance += 3;
		break;
	case BasicNote::D:
		distance += 5;
		break;
	case BasicNote::E:
		distance += 7;
		break;
	case BasicNote::F:
		distance += 8;
		break;
	case BasicNote::G:
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

int Note::getSemitoneDistance(const Note &other) const
{
	int thisDistance{ getAbsoluteDistance() };
	int otherDistance{ other.getAbsoluteDistance() };
	
	if (thisDistance > otherDistance)
		return thisDistance - otherDistance;
	else
		return otherDistance - thisDistance;
}

Note Note::getOtherNote(const Interval &interval, bool getLowerNote) const
{
	int otherOctave{ octave };
	int otherBase{ static_cast<int>(base) };
	int otherOffset{ offset };

	if (!getLowerNote) {
		otherOctave += (interval.getBasicDistance() / 7);
		otherBase += (interval.getBasicDistance() % 7);

		// normalize otherBase to be within 0-6, adjust octave accordingly
		otherOctave += otherBase / 7;
		otherBase %= 7;

		Note intermediate{ static_cast<BasicNote>(otherBase), 0, otherOctave };
		//otherOffset = intermediate.getAbsoluteDistance() - interval.getSemitones() - getAbsoluteDistance();
		otherOffset = getAbsoluteDistance() + interval.getSemitones() - intermediate.getAbsoluteDistance();
	}
	else {
		otherOctave -= (interval.getBasicDistance() / 7);
		otherBase -= (interval.getBasicDistance() % 7);

		// normalize otherBase to be within 0-6, adjust octave accordingly
		// this works the same as above but without fancy modulus math
		// (otherBase at this point can be no lower than -6)
		if (otherBase < 0) {
			otherBase += 7;
			otherOctave -= 1;
		}

		Note intermediate{ static_cast<BasicNote>(otherBase), 0, otherOctave };
		otherOffset = getAbsoluteDistance() - interval.getSemitones() - intermediate.getAbsoluteDistance();
	}

	return Note(static_cast<BasicNote>(otherBase), otherOffset, otherOctave);
}

Interval Note::getInterval(const Note & other) const
{
	int basicDistance = getBasicDistance(other);
	int semitones = getSemitoneDistance(other);
	return Interval(basicDistance, semitones);
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
	if (note.getOffset() < -2) {
		os << "(b^" << std::abs(note.getOffset()) << ")";
	}
	else if (note.getOffset() == -2)
		os << "bb";
	else if (note.getOffset() == -1)
		os << "b";
	else if (note.getOffset() == 1)
		os << "#";
	else if (note.getOffset() == 2)
		os << "##";
	else if (note.getOffset() > 2) {
		os << "(#^" << note.getOffset() << ")";
	}

	// Print octave
	os << note.getOctave();

	return os;
}
