#include <sstream>

#include "MusicReader.h"
#include "MusicParser.hxx"
#include "MusicLexer.h"

void MusicReader::ReadMusicInteractive(bool debug){
    MusicParserResult out;
    out.interactive = true;
    yy::MusicLexer lexer(&std::cin);
    yy::MusicParser parser(&lexer, &out);
	
	if (debug) {
		parser.set_debug_stream(std::cout);
		parser.set_debug_level(1);
	}

	std::cout << "Welcome to Centric" << std::endl << "> ";

    parser.parse();
}

MusicParserResult MusicReader::parse(const std::string& expr){
    MusicParserResult out;
    std::istringstream in(expr);
    yy::MusicLexer lexer(&in);
    yy::MusicParser parser(&lexer, &out);
    parser.parse(); // TODO error check
    return out;
}

Note MusicReader::readNote(const std::string& expr){
    return MusicReader::parse(expr).noteResult;
}
