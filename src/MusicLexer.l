%option c++
%option 8bit warn nodefault
%option noyywrap

%{
    #include <stdexcept>
    #include "MusicParser.hxx"
    #include "MusicLexer.h"

    // utility macros to simplify the actions
    #define YIELD_TOKEN(tok, val, type)     yylval->build<type>(val); \
                                            return yy::MusicParser::token::T_##tok;

    #define YY_TXT                  std::string(yytext, yyleng)

    #define YY_USER_ACTION          yylloc->columns(yyleng);
%}

%%

 /* code to be executed at every yylex() call */
%{
    yylloc->step();
%}

[[:digit:]]+                yylval->build<double>(std::atof(yytext)); return yy::MusicParser::token::T_NUM;

[[:blank:]]                 {/* whitespace */}
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
