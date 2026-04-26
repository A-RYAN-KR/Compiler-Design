%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "parser.tab.h"

extern int yyline;
%}

%option noyywrap
%option noinput
%option nounput

%%

"class"         { return CLASS; }
"public"        { return PUBLIC; }
"private"       { return PRIVATE; }
"protected"     { return PROTECTED; }
"static"        { return STATIC; }
"void"          { return VOID; }
"int"           { return INT; }
"double"        { return DOUBLE; }
"float"         { return FLOAT; }
"long"          { return LONG; }
"char"          { return CHAR; }
"boolean"       { return BOOLEAN; }
"String"        { return STRING_TYPE; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"for"           { return FOR; }
"return"        { return RETURN; }
"new"           { return NEW; }
"true"          { yylval.bval = 1; return BOOL_LIT; }
"false"         { yylval.bval = 0; return BOOL_LIT; }
"null"          { return NULL_LIT; }
"System.out.println"  { return SYSOUT_PRINTLN; }
"System.out.print"    { return SYSOUT_PRINT; }

[a-zA-Z_][a-zA-Z0-9_]*   { yylval.sval = strdup(yytext); return IDENTIFIER; }
[0-9]+\.[0-9]+([fFdD])?  { yylval.dval = atof(yytext); return DOUBLE_LIT; }
[0-9]+[lL]                { yylval.ival = atoi(yytext); return INT_LITERAL; }
[0-9]+                    { yylval.ival = atoi(yytext); return INT_LITERAL; }
\"([^"\\]|\\.)*\"         { yylval.sval = strdup(yytext); return STRING_LIT; }
\'([^'\\]|\\.)\'          { yylval.cval = yytext[1]; return CHAR_LIT; }

"++"    { return INCREMENT; }
"--"    { return DECREMENT; }
"=="    { return EQ; }
"!="    { return NEQ; }
"<="    { return LTE; }
">="    { return GTE; }
"&&"    { return AND; }
"||"    { return OR; }
"<<"    { return SHL; }
">>"    { return SHR; }
"+="    { return PLUS_ASSIGN; }
"-="    { return MINUS_ASSIGN; }
"*="    { return TIMES_ASSIGN; }
"/="    { return DIVIDE_ASSIGN; }
"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return TIMES; }
"/"     { return DIVIDE; }
"%"     { return MODULO; }
"<"     { return LT; }
">"     { return GT; }
"!"     { return NOT; }
"&"     { return BITAND; }
"|"     { return BITOR; }
"^"     { return BITXOR; }
"~"     { return BITNOT; }
"="     { return ASSIGN; }
"("     { return LPAREN; }
")"     { return RPAREN; }
"{"     { return LBRACE; }
"}"     { return RBRACE; }
"["     { return LBRACKET; }
"]"     { return RBRACKET; }
","     { return COMMA; }
";"     { return SEMICOLON; }
"."     { return DOT; }

\n          { yyline++; }
[ \t\r]+    { /* skip whitespace */ }
"//".*      { /* skip line comments */ }
"/*"([^*]|\*+[^*/])*\*+"/" { /* skip block comments - count newlines */
    const char *p = yytext;
    while (*p) { if (*p == '\n') yyline++; p++; }
}

.           { fprintf(stderr, "Lexical Error: Unknown character '%s' at line %d\n", yytext, yyline); }

%%
