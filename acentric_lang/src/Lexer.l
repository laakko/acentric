%option c++
%option 8bit warn nodefault
%option noyywrap
%option nounistd

%{
    #include <stdexcept>
    #include "Parser.hxx"
    #include "Lexer.h"

	#if _WIN32
		#include <io.h> // Provides Windows version of isatty()
	#endif

	#if __linux__
		#include <unistd.h>
	#endif

    yy::location loc;

    #define YY_USER_ACTION loc.columns(yyleng);
%}

%%

%{
    // Run this code on every yylex() call
    loc.step();
%}

[ABCDEFG]       { return yy::MusicParser::make_BASIC_NOTE(*yytext, loc); }
"R"             { return yy::MusicParser::make_REST(loc); }
"#"             { return yy::MusicParser::make_SHARP(loc);}
"b"             { return yy::MusicParser::make_FLAT(loc); }
[PmMda]         { return yy::MusicParser::make_INTERVAL_TYPE(*yytext, loc); }
"-"             { return yy::MusicParser::make_MINUS_SIGN(loc); }
"+"             { return yy::MusicParser::make_PLUS_SIGN(loc); }
"_"             { return yy::MusicParser::make_UNDERSCORE(loc); }
[\.]+           { return yy::MusicParser::make_DOTS(strlen(yytext), loc); }
"^"             { return yy::MusicParser::make_CARAT(loc); }
"("             { return yy::MusicParser::make_LPAREN(loc); }
")"             { return yy::MusicParser::make_RPAREN(loc); }
":"				{ return yy::MusicParser::make_COLON(loc); }
";"             { return yy::MusicParser::make_SEMICOLON(loc); }
"0"             { return yy::MusicParser::make_ZERO(loc); }

[1-9][0-9]*  {
    int n = std::stoi(yytext); // TODO check out of range
    return yy::MusicParser::make_POS_INTEGER(n, loc);
}

[ \t]+          { loc.step(); }
\\\r?\n         { loc.lines (yyleng); loc.step(); }
\r?\n           { loc.lines (yyleng); loc.step(); return yy::MusicParser::make_NEWLINE(loc); }
.               { std::cout << "Unhandled character: " << yytext << std::endl; }
<<EOF>>         { return yy::MusicParser::make_END(loc); }

%%

acentric_lang::Lexer::Lexer(std::istream* in, std::ostream* out)
    : yyFlexLexer(in, out)
{
}

int yyFlexLexer::yylex()
{
    throw std::logic_error(
        "The yylex() exists for technical reasons and must not be used.");
}
