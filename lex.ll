%{
/*****************************************************************************
 *
 *  lex.ll
 *  by oZ/acy
 *  (c) 2005-2011 oZ/acy.  ALL RIGHTS RESERVED.
 *
 *  Metis ãLèqÇÃéöãÂâêÕäÌ
 *
 ****************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include "parser.h"
#include "parse.h"

int linenum_G;
int yyerror(char *s);

namespace {

char* strdup_(const char* str)
{
  using namespace std;
  size_t len = std::strlen(str);
  char* x = (char*)std::malloc(len + 1);
  if (!x)
    return NULL;
  std::memcpy(x, str, len + 1);
  return x;
}

std::ostringstream* oss = NULL;

}




%}

%option never-interactive
%option stack

IDENT [a-zA-Z_]([a-zA-Z0-9_+*:]|-)*


%x ELM
%x STR
%x ATTR
%x COMMENT
%x CREF


%%

"@"  { yy_push_state(ELM); return S_AT; }

<ELM>"@"      { return S_AT; }
<ELM>"{"      {
                yy_push_state(STR);
                oss = new std::ostringstream;
                return S_LBRACE;
              }
<ELM>"}"      {
                yy_pop_state();
                oss = new std::ostringstream;
                return S_RBRACE;
              }
<ELM>;        {
                yy_pop_state();
                oss = new std::ostringstream;
                return S_SEMICOLON;
              }
<ELM>:        return S_COLON;
<ELM>=        return S_EQU;
<ELM>{IDENT}  { yylval.text = strdup_(yytext);  return S_IDENT; }
<ELM>"["      { BEGIN(ATTR); return S_LBRACKET; }

<ELM>[ \t]  /* space */
<ELM>\n     ++linenum_G;

<ELM>. yyerror("illegal input (element)");


<ATTR>"]"      { BEGIN(ELM); return S_RBRACKET; }
<ATTR>{IDENT}  { yylval.text = strdup_(yytext);  return S_IDENT; }
<ATTR>"{"      {
                 yy_push_state(STR);
                 oss = new std::ostringstream;
                 return S_LBRACE;
               }
<ATTR>"}"      {
                 oss = new std::ostringstream;
                 return S_RBRACE;
               }

<ATTR>","      return S_COMMA;
<ATTR>[ \t]  /* space */
<ATTR>\n     ++linenum_G;

<ATTR>. yyerror("illegal input (attribute)");




<STR>"@"  {
            yy_push_state(ELM);
            unput('@');
            yylval.text = strdup_(oss->str().c_str());
            delete oss;
            oss = NULL;
            return S_STRDATA;
          }

<STR>"}"  {
            yy_pop_state();
            unput('}');
            yylval.text = strdup_(oss->str().c_str());
            delete oss;
            oss = NULL;
            return S_STRDATA;
          }

<STR>&at;     *oss << "@";
<STR>&lb;     *oss << "{";
<STR>&rb;     *oss << "}";
<STR>&sharp;  *oss << "#";
<STR>&amp;    *oss << "&";

<STR>"&"    {
            yy_push_state(CREF);
            yylval.text = strdup_(oss->str().c_str());
            delete oss;
            oss = NULL;
            return S_STRDATA;
          }

<CREF>"#"x[0-9a-fA-F]+; {
                        yylval.text = strdup_(yytext);
                        oss = new std::ostringstream();
                        yy_pop_state();
                        return S_CHARREF;
                      }


<CREF>"#"[0-9]+; {
                   yylval.text = strdup_(yytext);
                   oss = new std::ostringstream();
                   yy_pop_state();
                   return S_CHARREF;
                 }

<CREF>{IDENT}; {
                  yylval.text = strdup_(yytext);
                  oss = new std::ostringstream();
                  yy_pop_state();
                  return S_CHARREF;
               }

<CREF>.  yyerror("illegal input (character reference)");




<STR>[^@&}#\n]*  *oss << yytext;
<STR>\n          { ++linenum_G;  *oss << "\n"; }
<STR>.           yyerror("illegal input (string)");


"#".*\n  { ++linenum_G; /* comment */ }
<STR>"#".*\n  {  ++linenum_G; /* comment */ }


"@"[ \t\n]*COMMENT[ \t\n]*"{$"       yy_push_state(COMMENT);
<STR>"@"[ \t\n]*COMMENT[ \t\n]*"{$"  yy_push_state(COMMENT);
<COMMENT>\n                         ++linenum_G;
<COMMENT>"$}"                        yy_pop_state();
<COMMENT>.
<COMMENT><<EOF>>                    yyerror("EOF in comment");


[ \t]
\n  ++linenum_G;

.  yyerror("illegal input");



%%

/*=====================================================
*  yyerror()
*
*  parse error éûÇ… bison ë§Ç©ÇÁåƒÇ—èoÇ≥ÇÍÇÈ
*===================================================*/
int yyerror(char *s)
{
  fprintf(stderr, "line %d: %s\n", linenum_G, s);
  exit(1);
}


/*===================================
*  yywrap()
*=================================*/
int yywrap(void)
{
  return 1;
}

/*==================================
*  initLexer()
*=================================*/
void initLexer(FILE* fp)
{
  yyin = fp;
}


/* eof */
