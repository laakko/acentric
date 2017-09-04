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

		out << "Welcome to Acentric" << std::endl << "> ";

		while (true) {
			try {
				parser.parse();
			}
			catch (const char* s) { // TODO replace with actual exception from acentric core (when implemented)
				out << s << std::endl;
				continue;
			}
			catch (const Parser::syntax_error& e) {
				out << e.what() << std::endl;
				continue;
			}
		}
	}

	acentric_lang::ParseResult Reader::parse(const std::string& expr) {
		acentric_lang::ParseResult result;
		std::istringstream in(expr);
		acentric_lang::Lexer lexer(in);
		acentric_lang::Parser parser(&lexer, &result);
		parser.parse(); // TODO error check
		return result;
	}

	acentric_core::Note Reader::readNote(const std::string& expr) {
		return Reader::parse(expr).noteResult; // TODO find a way to warn if input type doesn't match what's being returned
	}

}
