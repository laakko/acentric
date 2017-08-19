/* C++ parser interface */
%skeleton "lalr1.cc"
%require  "3.0"

%define parser_class_name {MusicParser}

/* add parser members (scanner, cb) and yylex parameters (loc, scanner) */
%parse-param  {yy::MusicLexer* lexer} {MusicParserResult* cb}
%locations

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

%token                  END     0   "end of file"
%token <int>            POSINT

%start statement

%%

statement    : %empty           { /* allow empty (or pure comment) lines */ }
             | POSINT              { cb->lolWut = $1; }
             ;

%%

void yy::MusicParser::error(const yy::MusicParser::location_type& l, const std::string& m)
{
    throw yy::MusicParser::syntax_error(l, m);
}
