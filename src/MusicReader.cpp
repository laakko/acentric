#include <sstream>

#include "MusicReader.h"
#include "MusicParser.hxx"
#include "MusicLexer.h"

void MusicReader::ReadMusicInteractive(){
    MusicParserResult out;
    out.interactive = true;
    yy::MusicLexer lexer(&std::cin);
    yy::MusicParser parser(&lexer, &out);
	parser.set_debug_stream(std::cout);
	parser.set_debug_level(1);

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
