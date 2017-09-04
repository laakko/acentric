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

    #define INTERACTIVE_OUT(output) \
        if (res->interactive) lexer->getyyout() << output << std::endl << "> ";

	#define INTERACTIVE_PROMPT_NEWLINE \
		if (res->interactive) lexer->getyyout() << "> ";

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
%type <acentric_core::Note> note
%type <acentric_core::Interval> interval

%left COLON
%left MINUS_SIGN PLUS_SIGN

%%

%start root;

root: %empty
    | root note NEWLINE							{ res->noteResult = $2; INTERACTIVE_OUT($2) }
    | root interval NEWLINE						{ res->intervalResult = $2; INTERACTIVE_OUT($2) }
	| root NEWLINE								{ INTERACTIVE_PROMPT_NEWLINE }
    ;

note: BASIC_NOTE offset octave                  { $$ = acentric_core::Note{$1, $2, $3}; }
    | note PLUS_SIGN interval					{ $$ = $1 + $3; }
	| note MINUS_SIGN interval					{ $$ = $1 - $3; }
	| interval PLUS_SIGN note					{ $$ = $3 + $1; }
    ;

offset: %empty									{ $$ = 0; }
    | FLAT offset								{ $$ = $2 - 1; }
    | SHARP offset								{ $$ = $2 + 1; }
    ;

octave: %empty									{ $$ = 4; }
    | POS_INTEGER								{ $$ = $1; }
	| ZERO										{ $$ = 0; }
    ;

interval: INTERVAL_TYPE POS_INTEGER				{ $$ = acentric_core::Interval{$1, $2}; }
	| note COLON note							{ $$ = $1.getInterval($3); }
	| interval PLUS_SIGN interval				{ $$ = $1 + $3; }
	| interval MINUS_SIGN interval				{ $$ = $1 - $3; }
	;

%%

void acentric_lang::Parser::error(const acentric_lang::Parser::location_type& l, const std::string& m)
{
    throw acentric_lang::Parser::syntax_error(l, m);
}
