#include <sstream>

#include "Reader.h"
#include "Parser.hxx"
#include "Lexer.h"

namespace acentric_lang {

	void Reader::doInteractive(bool debug) {
		acentric_lang::ParseResult out;
		out.interactive = true;
		acentric_lang::Lexer lexer(&std::cin);
		acentric_lang::Parser parser(&lexer, &out);

		if (debug) {
			parser.set_debug_stream(std::cout);
			parser.set_debug_level(1);
		}

		std::cout << "Welcome to Acentric" << std::endl << "> ";

		parser.parse();
	}

	acentric_lang::ParseResult Reader::parse(const std::string& expr) {
		acentric_lang::ParseResult out;
		std::istringstream in(expr);
		acentric_lang::Lexer lexer(&in);
		acentric_lang::Parser parser(&lexer, &out);
		parser.parse(); // TODO error check
		return out;
	}

	acentric_core::Note Reader::readNote(const std::string& expr) {
		return Reader::parse(expr).noteResult;
	}

}