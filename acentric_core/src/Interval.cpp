#include <regex>
#include "Interval.h"

namespace acentric_core {

	Interval::Interval(int basicDistance, int semitones)
	{
		if (basicDistance < 0)
			throw "bad basicInterval parameter in Interval ctor: " + std::to_string(basicDistance);
		this->basicDistance = basicDistance;

		if (semitones < 0)
			throw "bad semitones parameter in Interval ctor: " + std::to_string(semitones);
		this->semitones = semitones;
	}

	Interval::Interval(char intervalType, int intervalNumber, int offset) {
		if (intervalNumber < 1)
			throw "bad intervalNumber parameter in Interval ctor: " + std::to_string(intervalNumber);
		this->basicDistance = intervalNumber - 1;

		this->semitones = (this->basicDistance / 7) * 12;
		int remainder{ this->basicDistance % 7 };
		switch (intervalType) {
		case 'P':
			if (remainder == 0) break; // P1
			else if (remainder == 3) this->semitones += 5; // P4
			else if (remainder == 4) this->semitones += 7; // P5
			else throw "Invalid interval number given for interval class P";
			break;
		case 'm':
			if (remainder == 1) this->semitones += 1; // m2
			else if (remainder == 2) this->semitones += 3; // m3
			else if (remainder == 5) this->semitones += 8; // m6
			else if (remainder == 6) this->semitones += 10; // m7
			else throw "Invalid interval number given for interval class m";
			break;
		case 'M':
			if (remainder == 1) this->semitones += 2; // M2
			else if (remainder == 2) this->semitones += 4; // M3
			else if (remainder == 5) this->semitones += 9; // M6
			else if (remainder == 6) this->semitones += 11; // M7
			else throw "Invalid interval number given for interval class M";
			break;
		case 'd':
			// d8 special case
			if (remainder == 0 && this->semitones >= 12) {
				this->semitones -= 1;
				break;
			}
			if (remainder == 1) break; // d2
			else if (remainder == 2) this->semitones += 2; // d3
			else if (remainder == 3) this->semitones += 4; // d4
			else if (remainder == 4) this->semitones += 6; // d5
			else if (remainder == 5) this->semitones += 7; // d6
			else if (remainder == 6) this->semitones += 9; // d7
			else throw "Invalid interval number given for interval class d";
			break;
		case 'a':
			if (remainder == 0) this->semitones += 1; // a1
			else if (remainder == 1) this->semitones += 3; // a2
			else if (remainder == 2) this->semitones += 5; // a3
			else if (remainder == 3) this->semitones += 6; // a4
			else if (remainder == 4) this->semitones += 8; // a5
			else if (remainder == 5) this->semitones += 10; // a6
			else if (remainder == 6) this->semitones += 12; // a7
			else throw "Invalid interval number given for interval class a";
			break;
		default:
			throw "Invalid interval type given to Interval ctor (must be P, m, M, d, or a)";
		}

		// Add offset and check to make sure it's still positive
		this->semitones += offset;
		if (this->semitones < 0)
			throw "Invalid interval semitones calculated in Interval ctor (negative value)";
	}

	Interval Interval::operator+(const Interval & other)
	{
		int basicDistance = this->getBasicDistance() + other.getBasicDistance();
		int semitones = this->semitones + other.semitones;

		return Interval(basicDistance, semitones);
	}

	Interval Interval::operator-(const Interval & other)
	{
		int basicDistance = this->getBasicDistance() - other.getBasicDistance();
		if (basicDistance < 0)
			throw "Invalid interval subtraction (negative basic/note name distance)";

		int semitones = this->semitones - other.semitones;
		if (semitones < 0)
			throw "Invalid interval subtraction (negative semitone distance)";

		return Interval(basicDistance, semitones);
	}

	std::ostream & operator<<(std::ostream & os, const Interval & interval)
	{
		// Determine if the interval, unmodified, would be P or M
		bool perfect{ false };
		int basicDistance{ interval.getBasicDistance() };

		if (basicDistance % 7 == 0 || basicDistance % 7 == 3 || basicDistance % 7 == 4)
			perfect = true;
		else
			perfect = false; // so it would be Major instead

		// Find how many semitones the P/M interval would have
		int naturalSemitones{ (basicDistance / 7) * 12 };
		switch (basicDistance % 7) {
		case 0:
			break;
		case 1:
			naturalSemitones += 2;
			break;
		case 2:
			naturalSemitones += 4;
			break;
		case 3:
			naturalSemitones += 5;
			break;
		case 4:
			naturalSemitones += 7;
			break;
		case 5:
			naturalSemitones += 9;
			break;
		case 6:
			naturalSemitones += 11;
			break;
		}
		// The interval may dictate a different number of semitones than the "natural" M or P
		// Find this number...If it's within 1 or 2 it may have a canonical name like m, d or A
		// Otherwise display how many semitones away from the M or P the interval is
		int offset{ interval.getSemitones() - naturalSemitones };

		if ((offset < -2) || (offset == -2 && perfect)) {
			if (perfect)
				os << "(P";
			else
				os << "(M";
			os << offset << ")";
		}
		else if ((offset == -2 && !perfect) || (offset == -1 && perfect))
			os << "d";
		else if (offset == -1 && !perfect)
			os << "m";
		else if (offset == 0 && perfect)
			os << "P";
		else if (offset == 0 && !perfect)
			os << "M";
		else if (offset == 1)
			os << "a";
		else if (offset > 1) {
			if (perfect)
				os << "(P";
			else
				os << "(M";
			os << "+" << offset << ")";
		}

		os << basicDistance + 1;

		return os;
	}

}
