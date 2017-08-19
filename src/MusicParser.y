/* C++ parser interface */
%skeleton "lalr1.cc"
%require  "3.0"

%define parser_class_name {MusicParser}

/* add parser members (scanner, cb) and yylex parameters (loc, scanner) */
%parse-param  {yy::MusicLexer* lexer} {MusicParserResult* cb}
%locations

%define api.token.constructor

/* increase usefulness of error messages */
%define parse.error verbose

/* assert correct cleanup of semantic value objects */
%define parse.assert

%code requires {
    #include <stdexcept>
    #include <string>

    #include "location.hh"
    #include "Note.h"
    #include "BasicNote.h"

    namespace yy {
        class MusicLexer; // (Forward declaration to avoid circular dependency)
    };
    
    struct MusicParserResult {
        int lolWut = 0;
        Note noteResult;
    };
}

%code {
    #include <iostream>     // cerr, endl
    #include <utility>      // move
    #include <string>

    #include "MusicLexer.h"

    #define yylex lexer->lex
}

%define api.value.type variant
%define api.token.prefix {T_}

%token
    END 0
    REST
    SHARP
    FLAT
    MINUS_SIGN
    PLUS_SIGN
    UNDERSCORE
    CARAT
    LPAREN
    RPAREN
    WHITESPACE
    SEMICOLON
;

%token <char> BASIC_NOTE
%token <char> INTERVAL_TYPE
%token <int> NONNEG_INTEGER
%token <int> DOTS
%type <int> octave
%type <int> offset

%%

%start root;

root:
    | root note SEMICOLON
    ;

note:
    BASIC_NOTE offset octave                            { std::cout << "Found a note, letter " << $1 << ", offset " << $2 << ", octave " << $3 << std::endl; }
    ;

offset: { $$ = 0; }
    | FLAT offset  { $$ = $2 - 1; }
    | SHARP offset { $$ = $2 + 1; }
    ;

octave: { $$ = 4; }
    | NONNEG_INTEGER               { $$ = $1; }
    | MINUS_SIGN NONNEG_INTEGER  { $$ = -$2; }
    ;

%%

void yy::MusicParser::error(const yy::MusicParser::location_type& l, const std::string& m)
{
    throw yy::MusicParser::syntax_error(l, m);
}
