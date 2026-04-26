
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
     INT_LITERAL = 258,
     DOUBLE_LIT = 259,
     IDENTIFIER = 260,
     STRING_LIT = 261,
     BOOL_LIT = 262,
     CHAR_LIT = 263,
     CLASS = 264,
     PUBLIC = 265,
     PRIVATE = 266,
     PROTECTED = 267,
     STATIC = 268,
     VOID = 269,
     INT = 270,
     DOUBLE = 271,
     FLOAT = 272,
     LONG = 273,
     CHAR = 274,
     BOOLEAN = 275,
     STRING_TYPE = 276,
     IF = 277,
     ELSE = 278,
     WHILE = 279,
     FOR = 280,
     RETURN = 281,
     NEW = 282,
     NULL_LIT = 283,
     SYSOUT_PRINTLN = 284,
     SYSOUT_PRINT = 285,
     PLUS = 286,
     MINUS = 287,
     TIMES = 288,
     DIVIDE = 289,
     MODULO = 290,
     EQ = 291,
     NEQ = 292,
     LT = 293,
     GT = 294,
     LTE = 295,
     GTE = 296,
     AND = 297,
     OR = 298,
     NOT = 299,
     BITAND = 300,
     BITOR = 301,
     BITXOR = 302,
     BITNOT = 303,
     SHL = 304,
     SHR = 305,
     INCREMENT = 306,
     DECREMENT = 307,
     PLUS_ASSIGN = 308,
     MINUS_ASSIGN = 309,
     TIMES_ASSIGN = 310,
     DIVIDE_ASSIGN = 311,
     ASSIGN = 312,
     LPAREN = 313,
     RPAREN = 314,
     LBRACE = 315,
     RBRACE = 316,
     LBRACKET = 317,
     RBRACKET = 318,
     COMMA = 319,
     SEMICOLON = 320,
     DOT = 321,
     UMINUS = 322
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 20 "parser.y"

    double dval;
    char *sval;
    int bval;
    int ival;
    char cval;
    struct ASTNode *node;
    int jtype;
    int accmod;



/* Line 1676 of yacc.c  */
#line 132 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


