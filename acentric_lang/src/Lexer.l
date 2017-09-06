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

    acentric_lang::location loc;

    #define YY_USER_ACTION loc.columns(yyleng);

	using acentric_lang::Parser;
%}

%%

%{
    // Run this code on every yylex() call
    loc.step();
%}

[ABCDEFG]       { return Parser::make_BASIC_NOTE(*yytext, loc); }
"#"             { return Parser::make_SHARP(loc);}
"0"             { return Parser::make_ZERO(loc); }
"b"             { return Parser::make_FLAT(loc); }
"R"             { return Parser::make_REST(loc); }
[PmMda]         { return Parser::make_INTERVAL_TYPE(*yytext, loc); }
"-"             { return Parser::make_MINUS_SIGN(loc); }
"+"             { return Parser::make_PLUS_SIGN(loc); }
"_"             { return Parser::make_UNDERSCORE(loc); }
[\.]+           { return Parser::make_DOTS(strlen(yytext), loc); }
"^"             { return Parser::make_CARAT(loc); }
"("             { return Parser::make_LPAREN(loc); }
")"             { return Parser::make_RPAREN(loc); }
":"				{ return Parser::make_COLON(loc); }
";"             { return Parser::make_SEMICOLON(loc); }

[1-9][0-9]*  {
    int n = std::stoi(yytext); // TODO check out of range
    return Parser::make_POS_INTEGER(n, loc);
}

[ \t]           { loc.step(); }
\\\r?\n         { loc.lines(); loc.step(); }
\r?\n           { loc.lines(); loc.step(); return Parser::make_NEWLINE(loc); }
.               { yyin.ignore(INT_MAX, '\n'); yyin.putback('\n'); return Parser::make_UNHANDLED_CHAR(*yytext, loc); }
<<EOF>>         { return Parser::make_END(loc); }

%%

acentric_lang::Lexer::Lexer(std::istream& in, std::ostream& out)
    : yyFlexLexer(&in, &out)
{
}

int yyFlexLexer::yylex()
{
    throw std::logic_error(
        "yyFlexLexer::yylex() is unused in this flex/bison setup. Use acentric_lang::Lexer::lex() instead.");
}
