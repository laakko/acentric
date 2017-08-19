#include <sstream>

#include "MusicReader.h"
#include "MusicParser.hxx"
#include "MusicLexer.h"

int MusicReader::parseInt(const std::string& expr)
{
    MusicParserResult out;
    std::istringstream in(expr);
    yy::MusicLexer lexer(&in);
    yy::MusicParser parser(&lexer, &out);

    int result = parser.parse();

    return out.lolWut;
}
