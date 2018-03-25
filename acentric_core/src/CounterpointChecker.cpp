#include "CounterpointChecker.h"

acentric_core::CounterpointChecker::CounterpointChecker(const std::vector<Note>& cantusFirmus, const std::vector<Note>& counterpoint) :
	cantusFirmus(cantusFirmus),
	counterpoint(counterpoint)
{
	if (cantusFirmus.size() != counterpoint.size()) {
		throw "Different-sized cantus firmus and counterpoint passed to CounterpointChecker constructor";
	}
}

bool acentric_core::CounterpointChecker::counterpointIsValid() const
{
	// Go through the rules...Make this more customizable and IO-friendly later



	return true;
}
