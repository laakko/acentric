/* C++ parser interface */
%skeleton "lalr1.cc"
%require  "3.0"

%define parser_class_name {Parser}
%define api.namespace {acentric_lang}

%parse-param  {acentric_lang::Lexer* lexer} {acentric_lang::ParseResult* res}
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
	#include "Chord.h"

    namespace acentric_lang {
        class Lexer; // (Forward declaration to avoid circular dependency)

		struct ParseResult {
			bool interactive = false;
			acentric_core::Note noteResult;
			acentric_core::Interval intervalResult;
		};

    };
}

%code {
    #include <iostream>     // cerr, endl
    #include <utility>      // move
    #include <string>

    #include "Lexer.h"

    #define yylex lexer->lex

    #define OUT_RESULT(output) \
        if (res->interactive) lexer->getyyout() << output;

	#define OUT_ERROR \
		if (res->interactive) lexer->getyyout() << "Syntax error";

	#define OUT_NEWLINE \
		if (res->interactive) lexer->getyyout() << std::endl;

	#define OUT_PROMPT \
		if (res->interactive) lexer->getyyout() << "> ";

	#define OUT_UNHANDLED_CHAR(output) \
		if (res->interactive) lexer->getyyout() << "Syntax error";

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
	STAR
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
%token <char> UNHANDLED_CHAR
%token <int> POS_INTEGER
%token <int> DOTS
%type <int> octave
%type <int> offset
%type <acentric_core::Note> note
%type <acentric_core::Interval> interval
%type <std::vector<acentric_core::Interval>> interval_list
%type <acentric_core::Chord> chord

%left COLON
%left MINUS_SIGN PLUS_SIGN

%%

%start root;

root: %empty
    | root complete_phrase NEWLINE				{ OUT_NEWLINE OUT_PROMPT }
	| root complete_phrase error NEWLINE		{ OUT_NEWLINE OUT_ERROR OUT_NEWLINE OUT_PROMPT }
	| root error NEWLINE						{ OUT_ERROR OUT_NEWLINE OUT_PROMPT }
	| root NEWLINE								{ OUT_PROMPT }
    ;

complete_phrase:
	  note										{ res->noteResult = $1; OUT_RESULT($1) }
	| interval									{ res->intervalResult = $1; OUT_RESULT($1) }
/*	| interval_list
		{
			for (auto interval : $1) {
				std::cout << interval << std::endl;
			}
		} */
	| chord										{ OUT_RESULT($1) }
	| UNHANDLED_CHAR							{ OUT_UNHANDLED_CHAR($1) }
	;

note: BASIC_NOTE offset octave					{ $$ = acentric_core::Note{$1, $2, $3}; }
    | note PLUS_SIGN interval					{ $$ = $1 + $3; }
	| note MINUS_SIGN interval					{ $$ = $1 - $3; }
	| interval PLUS_SIGN note					{ $$ = $3 + $1; }
    ;

offset: %empty									{ $$ = 0; }
    | FLAT offset								{ $$ = $2 - 1; }
    | SHARP offset								{ $$ = $2 + 1; }
    ;

octave: %empty									{ $$ = 4; }
    | POS_INTEGER								{ $$ = $1; } /* need(?) to add negative octaves back in at some point */
	| ZERO										{ $$ = 0; }
    ;

interval: INTERVAL_TYPE POS_INTEGER				{ $$ = acentric_core::Interval{$1, $2}; }
	| note COLON note							{ $$ = $1.getInterval($3); }
	| interval PLUS_SIGN interval				{ $$ = $1 + $3; }
	| interval MINUS_SIGN interval				{ $$ = $1 - $3; }
	;

interval_list:	%empty							{ $$ = std::vector<acentric_core::Interval>{}; }
	| interval interval_list					{ $2.insert($2.begin(), $1); $$ = std::move($2); }
	| interval UNDERSCORE interval_list			{ $3.insert($3.begin(), $1); $$ = std::move($3); }
	;

chord:
	  note STAR interval_list					{ $$ = acentric_core::Chord{$1, $3}; }
	;

%%

void acentric_lang::Parser::error(const acentric_lang::Parser::location_type& l, const std::string& m)
{
    //throw acentric_lang::Parser::syntax_error(l, m);
}
