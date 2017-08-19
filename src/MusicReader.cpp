#include <sstream>

#include "MusicReader.h"
#include "MusicParser.hxx"
#include "MusicLexer.h"

MusicParserResult MusicReader::parse(const std::string& expr){
    MusicParserResult out;
    std::istringstream in(expr);
    yy::MusicLexer lexer(&in);
    yy::MusicParser parser(&lexer, &out);
    parser.parse(); // TODO error check
    return out;
}

int MusicReader::parseInt(const std::string& expr)
{
    return MusicReader::parse(expr).lolWut;
}

Note MusicReader::parseNote(const std::string& expr){
    return MusicReader::parse(expr).noteResult;
}
