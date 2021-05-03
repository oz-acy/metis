/*
 * Copyright 2005-2021 oZ/acy (名賀月晃嗣)
 * Redistribution and use in source and binary forms, 
 *     with or without modification, 
 *   are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/*
 * @file parse.yy
 * @author oZ/acy
 *
 */

%skeleton "lalr1.cc"
%require "3.0"

%defines
%define api.parser.class {Parser}

/* 構文解析器の屬性及び構築子引數の追加(らしい) */
%parse-param { metis::Lexer& lexer } { std::unique_ptr<metis::Element>& rootE }

/* 字句解析器を呼び出すときの追加パラメタ(らしい) */
%lex-param { metis::Lexer& lexer }

%code requires
{
#include <string>
#include <iostream>
#include "data.h"

//#include <cstdlib>
//#include <cstdio>

namespace metis { class Lexer; }
}


%code
{
int
yylex(
  metis::Parser::semantic_type* yylval,
  metis::Parser::location_type* location,
  metis::Lexer& lexer);
}


/*#include "parser.h"*/

%locations
%define api.namespace{metis}
%define parse.error verbose
%define api.value.type variant


/* 終端記號 */
%token <std::string> ID "identifier"
%token <std::string> CHARREF "character reference"
%token <std::string> STRDATA "string data"

/* 非終端記號 */
%type<std::unique_ptr<metis::Element>> element struct_element
%type<std::unique_ptr<metis::Element>> empty_element element_head
%type<std::list<std::unique_ptr<metis::Datum>>> data_list attributes attr_list
%type<std::unique_ptr<metis::Attribute>> attribute
%type<std::unique_ptr<metis::StringData>> string

/*
%type<dlist> data_list attributes attr_list
%type<attr> attribute
%type<str> string
*/


//namespace {

//metis::Element* rootElement_SG;
//metis::Element* current_SG;

//inline std::string createString_SF(char* dupstr)
//{
//  using namespace std;
//  string ret(dupstr);
//  free(dupstr);
//  return ret;
//}


//}//end of namespace

//extern int linenum_G;

// プロトタイプ宣言 (yylex, yyerror) for C++
//int yylex(void);
//int yyerror(char*);


//%}

/*
%union {
  char* text;
  metis::Element* elm;
  metis::Attribute* attr;
  std::list<metis::Datum*>* dlist;
  metis::StringData* str;
}
*/



//%token <text> S_IDENT S_STRDATA S_CHARREF
//%token S_AT S_LBRACE S_RBRACE S_LBRACKET S_RBRACKET
//%token S_COMMA
//%token S_AND S_SEMICOLON S_COLON S_EQU

//%type<elm> element struct_element empty_element element_head
//%type<dlist> data_list attributes attr_list
//%type<attr> attribute
//%type<str> string

//%start top_level

%%
top_level
: element
{
  rootE = std::move($1);
  //rootElement_SG = $1;  //or rootElement = std::move($1);
}
;

element
: struct_element
{
  $$ = std::move($1);
}
| empty_element
{
  $$ = std::move($1);
}
;

element_head
: '@' ID
{
  $$ = std::make_unique<metis::Element>($2);
}
;

empty_element
: element_head attributes ';'
{
  $$ = std::move($1);
  $$->children() = std::move($2);
}
;

struct_element
: element_head attributes '{' data_list '}'
{
  $$ = std::move($1);
  $$->children() = std::move($2);
  $$->children().splice($$->children().end(), $4);

  //$$->children() = *$2;
  //$$->children().splice($$->children().end(), *$4);
  //delete $4;
  //delete $2;
  //current_SG = $$->parent();
}
;


data_list
:
{
  $$ = std::list<std::unique_ptr<metis::Datum>>();
}
| data_list element
{
  $$ = std::move($1);
  $$.push_back(std::move($2));
}
| data_list string
{
  $$ = std::move($1);
  $$.push_back(std::move($2));
}
;


attributes
:
{
  $$ = std::list<std::unique_ptr<metis::Datum>>();
}
| '[' attr_list ']'
{
  $$ = std::move($2);
}

attr_list
: attribute
{
  $$ = std::list<std::unique_ptr<metis::Datum>>();
  $$.push_back(std::move($1));
}
| attr_list ',' attribute
{
  $$ = std::move($1);
  $$.push_back(std::move($3));
}
;


attribute
: ID '{' string '}'
{
  $$ = std::make_unique<metis::Attribute>($1, std::move($3));
}


string
: STRDATA
{
  $$ = std::make_unique<metis::StringData>();
  $$->push_back(std::make_unique<metis::NormalString>($1));
}
| CHARREF
{
  $$ = std::make_unique<metis::StringData>();
  $$->push_back(std::make_unique<metis::CharReference>($1));
}
| string STRDATA
{
  $$ = std::move($1);
  $$->push_back(std::make_unique<metis::NormalString>($2));
}
| string CHARREF
{
  $$ = std::move($1);
  $$->push_back(std::make_unique<metis::CharReference>($2));
}
;




%%
void metis::Parser::error(const location_type& l, const std::string& m)
{
  std::cerr
    << "error at "
    << (int)l.begin.line << ':' << (int)l.begin.column << " - "
    << (int)l.end.line << ':' << (int)l.end.column << std::endl;
}




//// 以下OLD ////////
/*
void initLexer(FILE*);

metis::Element* metis::Parser::parse(const std::string& path)
{
  using namespace std;
  linenum_G = 1;
  rootElement_SG = NULL;
  current_SG = NULL;

  FILE* fp = fopen(path.c_str(), "r");
  if (!fp)
    return NULL;
  initLexer(fp);
  yyparse();
  fclose(fp);
  return rootElement_SG;
}
*/


/* eof */
