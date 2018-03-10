#ifndef COUNTERPOINT_CHECKER_H
#define COUNTERPOINT_CHECKER_H

#include <Note.h>

namespace acentric_core {

	class CounterpointChecker {
	private:
		std::vector<Note> cantusFirmus;
		std::vector<Note> counterpoint;

	public:
		// Will eventually add options for scoring and even which rules to use/ignore
		// Make sure to validate (both vectors must be same length)
		CounterpointChecker(const std::vector<Note>& cantusFirmus, const std::vector<Note>& countpoint);

		// The big one...validate rules (use internal functions?) for every note...use openmusictheory.com/firstSpecies.html list of rules
		bool counterpointIsValid() const;

		void setCounterpoint(const std::vector<Note> counterpoint) { this->counterpoint = counterpoint; };

	};

}

#endif