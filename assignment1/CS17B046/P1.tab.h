/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_P1_TAB_H_INCLUDED
# define YY_YY_P1_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CLASS = 258,
    PUBLIC = 259,
    STATIC = 260,
    VOID = 261,
    EXTENDS = 262,
    RETURN = 263,
    INT = 264,
    STRING = 265,
    BOOLEAN = 266,
    IF = 267,
    ELSE = 268,
    WHILE = 269,
    TRUEVAL = 270,
    FALSEVAL = 271,
    THIS = 272,
    NEW = 273,
    MAIN = 274,
    SYSTEMOUTPRINTLN = 275,
    DEFINE = 276,
    LENGTH = 277,
    LEFTC = 278,
    RIGHTC = 279,
    LEFTB = 280,
    RIGHTB = 281,
    LEFTSQ = 282,
    RIGHTSQ = 283,
    DOT = 284,
    HASH = 285,
    SEMICOLON = 286,
    COMMA = 287,
    EQUAL = 288,
    AND = 289,
    OR = 290,
    NOT = 291,
    PLUS = 292,
    MINUS = 293,
    MULT = 294,
    DIV = 295,
    LESS = 296,
    Integer = 297,
    Identifier = 298,
    ANDAND = 299,
    OROR = 300,
    NOTEQUAL = 301,
    LESSEQUAL = 302
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 330 "P1.y" /* yacc.c:1909  */

	int c_int;
	char* c_str;
	char c_char;
	struct List* list;	
	struct MacroNode* mnode;

#line 110 "P1.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_P1_TAB_H_INCLUDED  */
