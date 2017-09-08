#ifndef READER_H
#define READER_H

# include <string>
# include <vector>
#include "Note.h"

#include "Parser.hxx"

namespace acentric_lang {

	/*! The Reader class is a front-end to the parser for the Acentric language. It can either run in interactive mode or parse one-off strings.
	
	One-off parsing is not currently developed very well and is not recommended for general use...Unless you'd like to help develop it further! :)*/
	class Reader
	{
	public:
		/*! Start an interactive session. The lexer and parser are designed to be reentrant (i.e., allow many sessions at once) but this hasn't been tested
		and isn't likely to matter to anyone. If you try it and it doesn't work, please open an issue.
		
		Debug mode shows the trace of the Bison parser...If you're into that sort of thing.*/
		static void doInteractive(bool debug = false, std::ostream& err = std::cerr, std::ostream& out = std::cout, std::istream& in = std::cin);

		/*! A one-off method to parse a Note object from a string. This doesn't check for errors and isn't well-tested. If you try it and it doesn't work, 
		open an issue or a pull request (it shouldn't be too tough to fix). More methods for one-off parsing of other types (Intervals, Chords) may be 
		implemented in the future but are not currently prioritized.*/
		acentric_core::Note readNote(const std::string&);

	private:
		acentric_lang::ParseResult parse(const std::string&);
	};

}

#endif // READER_H
