#include <sstream>

#include "Reader.h"
#include "Parser.hxx"
#include "Lexer.h"

namespace acentric_lang {

	void Reader::doInteractive(bool debug, std::ostream& err, std::ostream& out, std::istream& in) {
		acentric_lang::ParseResult result;
		result.interactive = true;
		acentric_lang::Lexer lexer(in, out);
		acentric_lang::Parser parser(&lexer, &result);

		if (debug) {
			parser.set_debug_stream(err);
			parser.set_debug_level(1);
		}

		std::cout << "Welcome to Acentric" << std::endl << "> ";

		parser.parse();
	}

	acentric_lang::ParseResult Reader::parse(const std::string& expr) {
		acentric_lang::ParseResult out;
		std::istringstream in(expr);
		acentric_lang::Lexer lexer(in);
		acentric_lang::Parser parser(&lexer, &out);
		parser.parse(); // TODO error check
		return out;
	}

	acentric_core::Note Reader::readNote(const std::string& expr) {
		return Reader::parse(expr).noteResult;
	}

}
