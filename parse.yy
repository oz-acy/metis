%{
/*****************************************************************************
*
*  parse.yy
*  by oZ/acy
*  (c) 2005-2011 oZ/acy.  ALL RIGHTS RESERVED.
*
*  Metis 記述の構文解析器
*
*  update: 5 Oct MMXI
*****************************************************************************/

#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "parser.h"


namespace {

metis::Element* rootElement_SG;
metis::Element* current_SG;

inline std::string createString_SF(char* dupstr)
{
  using namespace std;
  string ret(dupstr);
  free(dupstr);
  return ret;
}


}//end of namespace

extern int linenum_G;

// プロトタイプ宣言 (yylex, yyerror) for C++
int yylex(void);
int yyerror(char*);


%}


%union {
  char* text;
  metis::Element* elm;
  metis::Attribute* attr;
  std::list<metis::Datum*>* dlist;
  metis::StringData* str;
}




%token <text> S_IDENT S_STRDATA S_CHARREF
%token S_AT S_LBRACE S_RBRACE S_LBRACKET S_RBRACKET
%token S_COMMA
%token S_AND S_SEMICOLON S_COLON S_EQU



%type<elm> element struct_element empty_element element_head
%type<dlist> data_list attributes attr_list
%type<attr> attribute
%type<str> string

%start top_level

%%


top_level
: element
{
  rootElement_SG = $1;
}
;

element
: struct_element
{
  $$ = $1;
}
| empty_element
{
  $$ = $1;
}
;


element_head
: S_AT S_IDENT
{
  $$ = new metis::Element($2, current_SG);
  current_SG = $$;
  std::free($2);
}
;

empty_element
: element_head attributes S_SEMICOLON
{
  $$ = $1;
  $$->children() = *$2;
  delete $2;
  current_SG = $$->parent();
}
;

struct_element
: element_head attributes S_LBRACE data_list S_RBRACE
{
  $$ = $1;
  $$->children() = *$2;
  $$->children().splice($$->children().end(), *$4);
  delete $4;
  delete $2;
  current_SG = $$->parent();
}
;


data_list
:
{
  $$ = new std::list<metis::Datum*>;
}
| data_list element
{
  $$ = $1;
  $$->push_back($2);
}
| data_list string
{
  $$ = $1;
  $$->push_back($2);
}
;


attributes
:
{
  $$ = new std::list<metis::Datum*>;
}
| S_LBRACKET attr_list S_RBRACKET
{
  $$ = $2;
}

attr_list
: attribute
{
  $$ = new std::list<metis::Datum*>;
  $$->push_back($1);
}
| attr_list S_COMMA attribute
{
  $$ = $1;
  $$->push_back($3);
}
;


attribute
: S_IDENT S_LBRACE string S_RBRACE
{
  $$ = new metis::Attribute($1, $3, current_SG);
  std::free($1);
}


string
: S_STRDATA
{
  $$ = new metis::StringData(current_SG);
  $$->push_back(new metis::NormalString($1));
  std::free($1);
}
| S_CHARREF
{
  $$ = new metis::StringData(current_SG);
  $$->push_back(new metis::CharReference($1));
  std::free($1);
}
| string S_STRDATA
{
  $$ = $1;
  $$->push_back(new metis::NormalString($2));
  std::free($2);
}
| string S_CHARREF
{
  $$ = $1;
  $$->push_back(new metis::CharReference($2));
  std::free($2);
}
;




%%

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



/* eof */
