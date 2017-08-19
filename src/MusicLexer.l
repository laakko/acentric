%option c++
%option 8bit warn nodefault
%option noyywrap

%{
    #include <stdexcept>
    #include "MusicParser.hxx"
    #include "MusicLexer.h"

    // utility macros to simplify the actions
    #define MAKE_TOKEN(tok, type, val)     yylval->build<type>(val); \
                                            return yy::MusicParser::token::T_##tok;

    #define YY_STRING                  std::string(yytext, yyleng)

    #define YY_USER_ACTION          yylloc->columns(yyleng);
%}

%%

 /* code to be executed at every yylex() call */
%{
    yylloc->step();
%}

[1-9][0-9]*                 MAKE_TOKEN(POSINT, int, std::atoi(yytext));

[ \t]                 {/* whitespace */}
\n                          yylloc->lines(1);
.                           { }

%%

yy::MusicLexer::MusicLexer(std::istream* in, std::ostream* out)
    : yyFlexLexer(in, out)
{
}

int yyFlexLexer::yylex()
{
    throw std::logic_error(
        "The yylex() exists for technical reasons and must not be used.");
}
