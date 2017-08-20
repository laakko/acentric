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
        bool interactive = false;
        Note noteResult;
    };
}

%code {
    #include <iostream>     // cerr, endl
    #include <utility>      // move
    #include <string>

    #include "MusicLexer.h"

    #define yylex lexer->lex

    #define INTERACTIVE_OUT(output) \
        if (cb->interactive) std::cout << output << std::endl;

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
%type <Note> note

%%

%start root;

root: %empty
    | root note SEMICOLON                       { cb->noteResult = $2; INTERACTIVE_OUT($2) }
    ;

note:
    BASIC_NOTE offset octave                    { $$ = Note{$1, $2, $3}; }
    ;

offset: %empty                                  { $$ = 0; }
    | FLAT offset                               { $$ = $2 - 1; }
    | SHARP offset                              { $$ = $2 + 1; }
    ;

octave: %empty                                  { $$ = 4; }
    | NONNEG_INTEGER                            { $$ = $1; }
    | MINUS_SIGN NONNEG_INTEGER                 { $$ = -$2; }
    ;

%%

void yy::MusicParser::error(const yy::MusicParser::location_type& l, const std::string& m)
{
    throw yy::MusicParser::syntax_error(l, m);
}
