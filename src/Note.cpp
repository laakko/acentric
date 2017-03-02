#include "Note.h"

Note::Note(BasicNote base, int offset, int octave)
{
	// TODO validate input
	this->base = base;
	if (offset < -2 || offset > 2)
		throw "bad offset given to Note constructor: " + std::to_string(offset);
	this->offset = offset;
	this->octave = octave;
}
