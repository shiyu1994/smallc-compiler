/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     INT = 258,
     ID = 259,
     SEMI = 260,
     COMMA = 261,
     TYPE = 262,
     LP = 263,
     RP = 264,
     LB = 265,
     RB = 266,
     LC = 267,
     RC = 268,
     STRUCT = 269,
     RETURN = 270,
     IF = 271,
     ELSE = 272,
     BREAK = 273,
     CONT = 274,
     FOR = 275,
     ASSIGNOP = 276,
     BINARYOP10 = 277,
     BINARYOP9 = 278,
     BINARYOP8 = 279,
     BINARYOP7 = 280,
     BINARYOP6 = 281,
     BINARYOP5 = 282,
     BINARYOP4 = 283,
     BINARYOP3 = 284,
     BINARYOP2 = 285,
     BINARYOP1 = 286,
     UNARYOP = 287,
     DOT = 288
   };
#endif
/* Tokens.  */
#define INT 258
#define ID 259
#define SEMI 260
#define COMMA 261
#define TYPE 262
#define LP 263
#define RP 264
#define LB 265
#define RB 266
#define LC 267
#define RC 268
#define STRUCT 269
#define RETURN 270
#define IF 271
#define ELSE 272
#define BREAK 273
#define CONT 274
#define FOR 275
#define ASSIGNOP 276
#define BINARYOP10 277
#define BINARYOP9 278
#define BINARYOP8 279
#define BINARYOP7 280
#define BINARYOP6 281
#define BINARYOP5 282
#define BINARYOP4 283
#define BINARYOP3 284
#define BINARYOP2 285
#define BINARYOP1 286
#define UNARYOP 287
#define DOT 288




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 118 "Syntax.y"
{
    tree *node;
}
/* Line 1529 of yacc.c.  */
#line 119 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

