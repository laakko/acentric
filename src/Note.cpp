#include <string>
#include <map>
#include "Note.h"

Note::Note(std::string humanName, Key key)
{
	// TODO error check
	pianoKeyNum = Note::s_note.at(humanName);
	this->key = key;
}

Note::Note(int pianoKeyNum, Key key)
{
	// TODO bounds check 1-88
	this->pianoKeyNum = pianoKeyNum;
	this->key = key;
}

int Note::octave() {
	if (pianoKeyNum <= 3) {
		return 0;
	}
	else if (pianoKeyNum == 88) {
		return 8;
	}
	else {
		return (pianoKeyNum + 8) % 12;
	}
}

std::string Note::name() {
	// TODO implement; this will be a big one since it must incorporate scale
	return "C";
}

// Human-readable -> integer representation
// TODO handle odd cases like Cb or E#
const std::map<std::string, int> Note::s_note{
	{ "A0", 1 },  { "A#0", 2 }, { "Bb0", 2 }, { "B0", 3 },
	{ "C1", 4 },  { "C#1", 5 }, { "Db1", 5 }, { "D1", 6 },
	{ "D#1", 7 }, { "Eb1", 7 }, { "E1", 8 },  { "F1", 9 },
	{ "F#1", 10 },{ "Gb1", 10 },{ "G1", 11 }, { "G#1", 12 },
	{ "Ab1", 12 },

	{ "A1", 13 }, { "A#1", 14 },{ "Bb1", 14 },{ "B1", 15 },
	{ "C2", 16 }, { "C#2", 17 },{ "Db2", 17 },{ "D2", 18 },
	{ "D#2", 19 },{ "Eb2", 19 },{ "E2", 20 }, { "F2", 21 },
	{ "F#2", 22 },{ "Gb2", 22 },{ "G2", 23 }, { "G#2", 24 },
	{ "Ab2", 24 },

	{ "A2", 25 }, { "A#2", 26 },{ "Bb2", 26 },{ "B2", 27 },
	{ "C3", 28 }, { "C#3", 29 },{ "Db3", 29 },{ "D3", 30 },
	{ "D#3", 31 },{ "Eb3", 31 },{ "E3", 32 }, { "F3", 33 },
	{ "F#3", 34 },{ "Gb3", 34 },{ "G3", 35 }, { "G#3", 36 },
	{ "Ab3", 36 },

	{ "A3", 37 }, { "A#3", 38 },{ "Bb3", 38 },{ "B3", 39 },
	{ "C4", 40 }, { "C#4", 41 },{ "Db4", 41 },{ "D4", 42 },
	{ "D#4", 43 },{ "Eb4", 43 },{ "E4", 44 }, { "F4", 45 },
	{ "F#4", 46 },{ "Gb4", 46 },{ "G4", 47 }, { "G#4", 48 },
	{ "Ab4", 48 },

	{ "A4", 49 }, { "A#4", 50 },{ "Bb4", 50 },{ "B4", 51 },
	{ "C5", 52 }, { "C#5", 53 },{ "Db5", 53 },{ "D5", 54 },
	{ "D#5", 55 },{ "Eb5", 55 },{ "E5", 56 }, { "F5", 57 },
	{ "F#5", 58 },{ "Gb5", 58 },{ "G5", 59 }, { "G#5", 60 },
	{ "Ab5", 60 },

	{ "A5", 61 }, { "A#5", 62 },{ "Bb5", 62 },{ "B5", 63 },
	{ "C6", 64 }, { "C#6", 65 },{ "Db6", 65 },{ "D6", 66 },
	{ "D#6", 67 },{ "Eb6", 67 },{ "E6", 68 }, { "F6", 69 },
	{ "F#6", 70 },{ "Gb6", 70 },{ "G6", 71 }, { "G#6", 72 },
	{ "Ab6", 72 },

	{ "A6", 73 }, { "A#6", 74 },{ "Bb6", 74 },{ "B6", 75 },
	{ "C7", 76 }, { "C#7", 77 },{ "Db7", 77 },{ "D7", 78 },
	{ "D#7", 79 },{ "Eb7", 79 },{ "E7", 80 }, { "F7", 81 },
	{ "F#7", 82 },{ "Gb7", 82 },{ "G7", 83 }, { "G#7", 84 },
	{ "Ab7", 84 },

	{ "A7", 85 },{ "A#7", 86 },{ "Bb7", 86 },{ "B7", 87 },
	{ "C8", 88 }
};

