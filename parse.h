/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     S_IDENT = 258,
     S_STRDATA = 259,
     S_CHARREF = 260,
     S_AT = 261,
     S_LBRACE = 262,
     S_RBRACE = 263,
     S_LBRACKET = 264,
     S_RBRACKET = 265,
     S_COMMA = 266,
     S_AND = 267,
     S_SEMICOLON = 268,
     S_COLON = 269,
     S_EQU = 270
   };
#endif
/* Tokens.  */
#define S_IDENT 258
#define S_STRDATA 259
#define S_CHARREF 260
#define S_AT 261
#define S_LBRACE 262
#define S_RBRACE 263
#define S_LBRACKET 264
#define S_RBRACKET 265
#define S_COMMA 266
#define S_AND 267
#define S_SEMICOLON 268
#define S_COLON 269
#define S_EQU 270




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 46 "parse.yy"

  char* text;
  metis::Element* elm;
  metis::Attribute* attr;
  std::list<metis::Datum*>* dlist;
  metis::StringData* str;



/* Line 1685 of yacc.c  */
#line 91 "parse.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


