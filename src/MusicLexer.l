%option c++
%option 8bit warn nodefault
%option noyywrap

%{
    #include <stdexcept>
    #include "MusicParser.hxx"
    #include "MusicLexer.h"

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
";"             { return yy::MusicParser::make_SEMICOLON(loc); }

[0-9]+  {
    int n = std::stoi(yytext); // TODO check out of range
    return yy::MusicParser::make_NONNEG_INTEGER(n, loc);
}

[ \t]+          { loc.step(); }
[\n]+           { loc.lines (yyleng); loc.step(); }
.               { std::cout << "Unhandled character: " << yytext << std::endl; }
<<EOF>>         { return yy::MusicParser::make_END(loc); }

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
