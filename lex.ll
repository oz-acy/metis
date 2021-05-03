%{
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
 *
 * @file lex.ll
 * @author oZ/acy
 * @brief Metis記述の字句解析器
 *
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>

#include "parser.h"
#include "lexer.h"


#undef YY_DECL
#define YY_DECL \
  int metis::Lexer::yylex(\
    metis::Parser::semantic_type& lval, \
    metis::Parser::location_type& loc)

/* ルールセクションのどのアクションよりも前に實行されるアクションの定義 */
#define YY_USER_ACTION loc.columns(yyleng);


//int linenum_G;
//int yyerror(char *s);
/*
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
*/



%}
%option c++
%option stack
%option never-interactive
%option yyclass="metis::Lexer"


  /* UTF8のASCII部分を除いたもの */
U2 [\xc2-\xdf]
U3 [\xe0-\xef]
U4 [\xf0-\xf4]
UC [\x80-\xbf]
UTF8L {U2}{UC}|{U3}{UC}{UC}|{U4}{UC}{UC}{UC}

IDENT ([[:alpha:]]|{UTF8L}|[:_])([[:alnum:]]|{UTF8L}|[._:-])*
  /* IDENT [a-zA-Z_]([a-zA-Z0-9_+*:]|-)*  */

DELIMITER "@"|"{"|"}"|";"|"["|"]"|","

%x ELM
%x STR
%x ATTR
%x COMMENT
%x CREF


%%
%{  /* yylex()の冒頭に置かれる */
  loc.step();
%}


  /* 以下、Element關聯 */
"@"  { yy_push_state(ELM); return '@'; }

<ELM>"@"  { return '@'; }
<ELM>"{"  {
    yy_push_state(STR);
    oss_.str("");
    oss_.clear();
    return '{';
  }
<ELM>"}"  {
    yy_pop_state();
    oss_.str("");
    oss_.clear();
    return '}';
  }
<ELM>;  {
    yy_pop_state();
    oss_.str("");
    oss_.clear();
    return ';';
  }
  /* <ELM>:        return S_COLON; 意圖不明 */
  /* <ELM>=        return S_EQU; 意圖不明 */
<ELM>{IDENT}  {
    lval.build<std::string>() = std::string(yytext);
    return metis::Parser::token::ID;
  }
<ELM>"["  {
    BEGIN(ATTR);
    return '[';
  }

<ELM>[ \t]+  { loc.step(); }
<ELM>\r\n|\r|\n  { loc.lines(); loc.step(); }

<ELM>. { return metis::Parser::token::YYUNDEF; }


  /* 以下、屬性關聯 */
<ATTR>"]"  {
    BEGIN(ELM);
    return ']';
  }
<ATTR>{IDENT}  {
    lval.build<std::string>() = std::string(yytext);
    return metis::Parser::token::ID;
  }
<ATTR>"{"  {
    yy_push_state(STR);
    oss_.str("");
    oss_.clear();
    return '{';
  }
<ATTR>"}"  {
    oss_.str("");
    oss_.clear();
    return '}';
  }
<ATTR>","  { return ','; }

<ATTR>[ \t]+  { loc.step(); }
<ATTR>\r\n|\r|\n  { loc.lines(); loc.step(); }

<ATTR>.  { return metis::Parser::token::YYUNDEF; }


<STR>"@"  {
    yy_push_state(ELM);
    unput('@');
    lval.build<std::string>() = oss_.str();
    oss_.str("");
    oss_.clear();
    return metis::Parser::token::STRDATA;
            //yylval.text = strdup_(oss->str().c_str());
            //delete oss;
            //oss = NULL;
            //return S_STRDATA;
  }

<STR>"}"  {
    yy_pop_state();
    unput('}');
    lval.build<std::string>() = oss_.str();
    oss_.str("");
    oss_.clear();
    return metis::Parser::token::STRDATA;
            //yylval.text = strdup_(oss->str().c_str());
            //delete oss;
            //oss = NULL;
            //return S_STRDATA;
  }

<STR>&at;  { oss_ << '@'; }
<STR>&lb;  { oss_ << '{'; }
<STR>&rb;  { oss_ << '}'; }
<STR>&sharp;  { oss_ << '#'; }
<STR>&amp;  { oss_ << '&'; }

<STR>"&"  {
    yy_push_state(CREF);
    lval.build<std::string>() = oss_.str();
    oss_.str("");
    oss_.clear();
    return metis::Parser::token::STRDATA;
            //yylval.text = strdup_(oss->str().c_str());
            //delete oss;
            //oss = NULL;
            //return S_STRDATA;
  }

<CREF>"#"x[0-9a-fA-F]+;  {
    lval.build<std::string>() = std::string(yytext);
    oss_.str("");
    oss_.clear();
    yy_pop_state();
    return metis::Parser::token::CHARREF;
                        //return S_CHARREF;
  }


<CREF>"#"[0-9]+;  {
    lval.build<std::string>() = std::string(yytext);
    oss_.str("");
    oss_.clear();
    yy_pop_state();
    return metis::Parser::token::CHARREF;
                   //yylval.text = strdup_(yytext);
                   //oss = new std::ostringstream();
                   //yy_pop_state();
                   //return S_CHARREF;
  }

<CREF>{IDENT};  {
    lval.build<std::string>() = std::string(yytext);
    oss_.str("");
    oss_.clear();
    yy_pop_state();
    return metis::Parser::token::CHARREF;
                  //yylval.text = strdup_(yytext);
                  //oss = new std::ostringstream();
                  //yy_pop_state();
                  //return S_CHARREF;
  }

<CREF>.  { return metis::Parser::token::YYUNDEF; }


<STR>[^@&}#\n]*  { oss_ << yytext; }
<STR>\r\n|\r|\n  { loc.lines(); oss_ << '\n'; }


<STR>.  { return metis::Parser::token::YYUNDEF; }


"#".*(\r\n|\r|\n)  { loc.lines(); loc.step(); /* comment */ }
<STR>"#".*(\r\n|\r|\n)  {  loc.lines(); loc.step(); /* comment */ }


"@"[ \t]*COMMENT[ \t]*"{$"  { yy_push_state(COMMENT); loc.step(); }
<STR>"@"[ \t]*COMMENT[ \t]*"{$"  { yy_push_state(COMMENT); loc.step(); }
<COMMENT>\r\n|\r|\n  { loc.lines(); loc.step(); /* comment */ }
<COMMENT>"$}"  { yy_pop_state(); loc.step(); }
<COMMENT>.     { loc.step(); }
<COMMENT><<EOF>>  { return metis::Parser::token::YYUNDEF; }


[ \t]  { loc.step(); }
\r\n|\r|\n  { loc.lines(); loc.step(); }

.  { return metis::Parser::token::YYUNDEF; }



%%

/* 構文解析器から呼び出す函數 */
int yylex(
  metis::Parser::semantic_type* yylval,
  metis::Parser::location_type* location,
  metis::Lexer& lexer)
{
  return lexer.yylex(*yylval, *location);
}


/*
 * EOFに達したときに呼ばれる函數。
 * 0を返すと、yyinが次の入力ファイルを指すやうに設定されたといふ假定で
 * 字句解析を續行する。
 * 非ゼロを返すと解析終了。
 */
int yyFlexLexer::yywrap()
{
  return 1;
}




//// 以下OLD ////////


/*=====================================================
*  yyerror()
*
*  parse error 時に bison 側から呼び出される
*===================================================*/
//int yyerror(char *s)
//{
//  fprintf(stderr, "line %d: %s\n", linenum_G, s);
//  exit(1);
//}


/*===================================
*  yywrap()
*=================================*/
//int yywrap(void)
//{
//  return 1;
//}

/*==================================
*  initLexer()
*=================================*/
//void initLexer(FILE* fp)
//{
//  yyin = fp;
//}


/* eof */
