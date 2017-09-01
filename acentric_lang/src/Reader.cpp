#include <sstream>

#include "Reader.h"
#include "Parser.hxx"
#include "Lexer.h"

void MusicReader::ReadMusicInteractive(bool debug){
    acentric_lang::ParserResult out;
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

acentric_lang::ParserResult MusicReader::parse(const std::string& expr){
    acentric_lang::ParserResult out;
    std::istringstream in(expr);
    acentric_lang::Lexer lexer(&in);
    acentric_lang::Parser parser(&lexer, &out);
    parser.parse(); // TODO error check
    return out;
}

Note MusicReader::readNote(const std::string& expr){
    return MusicReader::parse(expr).noteResult;
}
