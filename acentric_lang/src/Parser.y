/* C++ parser interface */
%skeleton "lalr1.cc"
%require  "3.0"

%define parser_class_name {MusicParser}

/* add parser members (scanner, cb) and yylex parameters (loc, scanner) */
%parse-param  {acentric_lang::Lexer* lexer} {MusicParserResult* cb}
%locations

%define api.token.constructor

/* increase usefulness of error messages */
%define parse.error verbose

%define parse.trace

/* assert correct cleanup of semantic value objects */
%define parse.assert

%code requires {
    #include <stdexcept>
    #include <string>

    #include "location.hh"
    #include "Note.h"
    #include "Interval.h"
    #include "BasicNote.h"

    namespace acentric_lang {
        class Lexer; // (Forward declaration to avoid circular dependency)
    };
    
    struct MusicParserResult {
        bool interactive = false;
        Note noteResult;
        Interval intervalResult;
    };
}

%code {
    #include <iostream>     // cerr, endl
    #include <utility>      // move
    #include <string>

    #include "Lexer.h"

    #define yylex lexer->lex

    #define INTERACTIVE_OUT(output) \
        if (cb->interactive) std::cout << output << std::endl << "> ";

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
	COLON
    SEMICOLON
    ZERO
    NEWLINE
;

%token <char> BASIC_NOTE
%token <char> INTERVAL_TYPE
%token <int> POS_INTEGER
%token <int> DOTS
%type <int> octave
%type <int> offset
%type <Note> note
%type <Interval> interval

%left COLON
%left MINUS_SIGN PLUS_SIGN

%%

%start root;

root: %empty
    | root note NEWLINE                       { cb->noteResult = $2; INTERACTIVE_OUT($2) }
    | root interval NEWLINE                   { cb->intervalResult = $2; INTERACTIVE_OUT($2) }
    ;

note: BASIC_NOTE offset octave                  { $$ = Note{$1, $2, $3}; }
    | note PLUS_SIGN interval					{ $$ = $1 + $3; }
	| note MINUS_SIGN interval					{ $$ = $1 - $3; }
	| interval PLUS_SIGN note					{ $$ = $3 + $1; }
    ;

offset: %empty                                  { $$ = 0; }
    | FLAT offset                               { $$ = $2 - 1; }
    | SHARP offset                              { $$ = $2 + 1; }
    ;

octave: %empty                                  { $$ = 4; }
    | POS_INTEGER                               { $$ = $1; }
	| ZERO										{ $$ = 0; }
    ;

interval: INTERVAL_TYPE POS_INTEGER                   { $$ = Interval{$1, $2}; }
	| LPAREN INTERVAL_TYPE PLUS_SIGN POS_INTEGER RPAREN POS_INTEGER		{ $$ = Interval{$2, $6, $4}; }
	| LPAREN INTERVAL_TYPE MINUS_SIGN POS_INTEGER RPAREN POS_INTEGER	{ $$ = Interval{$2, $6, -$4}; }
	| note COLON note							{ $$ = $1.getInterval($3); }
	| interval PLUS_SIGN interval				{ $$ = $1 + $3; }
	| interval MINUS_SIGN interval				{ $$ = $1 - $3; }
	;

%%

void yy::MusicParser::error(const yy::MusicParser::location_type& l, const std::string& m)
{
    throw yy::MusicParser::syntax_error(l, m);
}
