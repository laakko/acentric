#include <sstream>

#include "Reader.h"
#include "Parser.hxx"
#include "Lexer.h"

void MusicReader::ReadMusicInteractive(bool debug){
    ParserResult out;
    out.interactive = true;
    acentric_lang::Lexer lexer(&std::cin);
    yy::Parser parser(&lexer, &out);
	
	if (debug) {
		parser.set_debug_stream(std::cout);
		parser.set_debug_level(1);
	}

	std::cout << "Welcome to Acentric" << std::endl << "> ";

    parser.parse();
}

ParserResult MusicReader::parse(const std::string& expr){
    ParserResult out;
    std::istringstream in(expr);
    acentric_lang::Lexer lexer(&in);
    yy::Parser parser(&lexer, &out);
    parser.parse(); // TODO error check
    return out;
}

Note MusicReader::readNote(const std::string& expr){
    return MusicReader::parse(expr).noteResult;
}
