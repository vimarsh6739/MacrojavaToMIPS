%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "P1.tab.h"
	#include <string.h>
%}

digit [0-9]
uint_v (0|([1-9]{digit}*))
id  [a-zA-Z_][a-zA-Z0-9_]*
space "\t"|"\n"|" "

%%
"//".* {;}
"class" {yylval.c_str = strdup(yytext);return CLASS;}
"public" {yylval.c_str = strdup(yytext);return PUBLIC;}
"static" {yylval.c_str = strdup(yytext);return STATIC;}
"void" {yylval.c_str = strdup(yytext);return VOID;}
"extends" {yylval.c_str = strdup(yytext);return EXTENDS;}
"return" {yylval.c_str = strdup(yytext);return RETURN;}
"int" {yylval.c_str = strdup(yytext);return INT;}
"boolean" {yylval.c_str = strdup(yytext);return BOOLEAN;}
"if" {yylval.c_str = strdup(yytext);return IF;}
"else" {yylval.c_str = strdup(yytext);return ELSE;}
"while" {yylval.c_str = strdup(yytext);return WHILE;}
"true" {yylval.c_str = strdup(yytext);return TRUEVAL;}
"false" {yylval.c_str = strdup(yytext);return FALSEVAL;}
"this" {yylval.c_str = strdup(yytext);return THIS;}
"new" {yylval.c_str = strdup(yytext);return NEW;}
"main" {yylval.c_str = strdup(yytext);return MAIN;}
"System.out.println" {yylval.c_str = strdup(yytext);return SYSTEMOUTPRINTLN;}
"define" {yylval.c_str = strdup(yytext);return DEFINE;}
"length" {yylval.c_str = strdup(yytext);return LENGTH;}
"String" {yylval.c_str = strdup(yytext);return STRING;}

"(" {return LEFTC;}
")" {return RIGHTC;}
"{" {return LEFTB;}
"}" {return RIGHTB;}
"[" {return LEFTSQ;}
"]" {return RIGHTSQ;}
"." {return DOT;}
"#" {return HASH;}
";" {return SEMICOLON;}
"," {return COMMA;}

"=" {return EQUAL;}
"&" {return AND;}
"|" {return OR;}
"!" {return NOT;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MULT;}
"/" {return DIV;}
"<" {return LESS;}

"&&" {yylval.c_str = strdup(yytext);return ANDAND;}
"||" {yylval.c_str = strdup(yytext);return OROR;}
"!=" {yylval.c_str = strdup(yytext);return NOTEQUAL;}
"<=" {yylval.c_str = strdup(yytext);return LESSEQUAL;}

{id} {	yylval.c_str = (char*)malloc(strlen(yytext) * sizeof(char));
	  	strcpy(yylval.c_str, yytext); 
	  	return Identifier;
	 }
{uint_v} {yylval.c_int=atoi(yytext);return Integer;}
{space} {;}

%%

/* main()
{
  printf("Enter the input:\n");
  yylex();
}*/
