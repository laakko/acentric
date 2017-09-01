#ifndef READER_H
#define READER_H

# include <string>
# include <vector>
#include "Note.h"

#include "Parser.hxx"

namespace acentric_lang {

	class Reader : public acentric_lang::ParserResult
	{
	public:
		static void ReadMusicInteractive(bool debug = false);

		static Note readNote(const std::string&);

	private:
		static acentric_lang::ParserResult parse(const std::string&);
	};

}

#endif // READER_H
