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

    static yy::location loc;

    #define YY_USER_ACTION loc.columns(yyleng);
%}

%%

 /* code to be executed at every yylex() call */
%{
    loc.step();
%}

[1-9][0-9]*                 return yy::MusicParser::make_POSINT(std::atoi(yytext), loc);

[\n]+                       { loc.lines(yyleng); loc.step(); }
[ \t]                       { loc.step(); }
.                           { }
<<EOF>>                     return yy::MusicParser::make_END(loc);

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
