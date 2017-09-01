#ifndef READER_H
#define READER_H

# include <string>
# include <vector>
#include "Note.h"

#include "Parser.hxx"

namespace acentric_lang {

	class Reader : public acentric_lang::ParseResult
	{
	public:
		static void doInteractive(bool debug = false);

		static acentric_core::Note readNote(const std::string&);

	private:
		static acentric_lang::ParseResult parse(const std::string&);
	};

}

#endif // READER_H
