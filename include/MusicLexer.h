#ifndef MUSIC_LEXER_H
#define MUSIC_LEXER_H

#undef yyFlexLexer
#include <FlexLexer.h>
#include "MusicParser.hxx"

// Tell flex which function to define
#ifdef  YY_DECL
# undef YY_DECL
#endif
//#define YY_DECL                                 \
    yy::MusicParser::symbol_type yy::MusicLexer::lex(        \
                    yy::MusicParser::semantic_type* yylval,  \
                    yy::MusicParser::location_type* yylloc)
#define YY_DECL yy::MusicParser::symbol_type yy::MusicLexer::lex()


namespace yy
{
    // To feed data back to bison, the yylex method needs yylval and
    // yylloc parameters. Since the yyFlexLexer class is defined in the
    // system header <FlexLexer.h> the signature of its yylex() method
    // can not be changed anymore. This makes it necessary to derive a
    // scanner class that provides a method with the desired signature:

    class MusicLexer : public yyFlexLexer
    {
    public:
        explicit MusicLexer(std::istream* in=0, std::ostream* out=0);

        //yy::MusicParser::symbol_type lex(MusicParser::semantic_type* yylval,
        //                                 MusicParser::location_type* yylloc);
        yy::MusicParser::symbol_type lex();
    };
}

#endif // MUSIC_LEXER_H