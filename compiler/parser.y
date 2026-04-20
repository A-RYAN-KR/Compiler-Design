%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex(void);
extern int yyline;
extern char *yytext;
extern FILE *yyin;

void yyerror(const char *s);

extern ASTNode *ast_root;

/* Helper to parse JavaType from token types */
static JavaType current_type;
%}

%union {
    double dval;
    char *sval;
    int bval;
    int ival;
    char cval;
    struct ASTNode *node;
    int jtype;
    int accmod;
}

%token <ival> INT_LITERAL
%token <dval> DOUBLE_LIT
%token <sval> IDENTIFIER STRING_LIT
%token <bval> BOOL_LIT
%token <cval> CHAR_LIT

%token CLASS PUBLIC PRIVATE PROTECTED STATIC
%token VOID INT DOUBLE FLOAT LONG CHAR BOOLEAN STRING_TYPE
%token IF ELSE WHILE FOR RETURN NEW NULL_LIT
%token SYSOUT_PRINTLN SYSOUT_PRINT

%token PLUS MINUS TIMES DIVIDE MODULO
%token EQ NEQ LT GT LTE GTE
%token AND OR NOT
%token BITAND BITOR BITXOR BITNOT SHL SHR
%token INCREMENT DECREMENT
%token PLUS_ASSIGN MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN
%token ASSIGN
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token COMMA SEMICOLON DOT

%type <node> program class_list class_decl
%type <node> class_body class_member_list class_member
%type <node> method_decl field_decl
%type <node> statement_list statement block
%type <node> var_decl_stmt assign_stmt if_stmt while_stmt for_stmt return_stmt expr_stmt
%type <node> print_stmt
%type <node> expression primary postfix_expr
%type <node> opt_param_list param_list typed_param
%type <node> opt_arg_list arg_list
%type <node> for_init for_update
%type <jtype> type_spec
%type <accmod> access_mod opt_access_mod
%type <bval> opt_static

%left OR
%left AND
%left BITOR
%left BITXOR
%left BITAND
%left EQ NEQ
%left LT GT LTE GTE
%left SHL SHR
%left PLUS MINUS
%left TIMES DIVIDE MODULO
%right NOT BITNOT
%right UMINUS

%%

program:
    class_list                      { ast_root = $1; }
    | statement_list                { ast_root = $1; }
    ;

class_list:
    class_decl                      {
        $$ = ast_new_stmt_list();
        ast_add_item($$, $1);
    }
    | class_list class_decl         {
        ast_add_item($1, $2);
        $$ = $1;
    }
    ;

class_decl:
    opt_access_mod CLASS IDENTIFIER LBRACE class_body RBRACE {
        $$ = ast_new_class_decl($3, (AccessMod)$1, $5, yyline);
    }
    ;

opt_access_mod:
    /* empty */                     { $$ = ACC_DEFAULT; }
    | access_mod                    { $$ = $1; }
    ;

access_mod:
    PUBLIC                          { $$ = ACC_PUBLIC; }
    | PRIVATE                       { $$ = ACC_PRIVATE; }
    | PROTECTED                     { $$ = ACC_PROTECTED; }
    ;

opt_static:
    /* empty */                     { $$ = 0; }
    | STATIC                        { $$ = 1; }
    ;

class_body:
    class_member_list               { $$ = $1; }
    ;

class_member_list:
    /* empty */                     {
        $$ = ast_new_stmt_list();
    }
    | class_member_list class_member {
        ast_add_item($1, $2);
        $$ = $1;
    }
    ;

class_member:
    method_decl                     { $$ = $1; }
    | field_decl                    { $$ = $1; }
    ;

method_decl:
    opt_access_mod opt_static type_spec IDENTIFIER LPAREN opt_param_list RPAREN LBRACE statement_list RBRACE {
        $$ = ast_new_method_decl($4, (JavaType)$3, (AccessMod)$1, $2, $6, $9, yyline);
    }
    ;

field_decl:
    opt_access_mod opt_static type_spec IDENTIFIER ASSIGN expression SEMICOLON {
        ASTNode *n = ast_new_var_decl($4, (JavaType)$3, $6, yyline);
        n->access = (AccessMod)$1;
        n->is_static = $2;
        $$ = n;
    }
    | opt_access_mod opt_static type_spec IDENTIFIER SEMICOLON {
        ASTNode *n = ast_new_var_decl($4, (JavaType)$3, NULL, yyline);
        n->access = (AccessMod)$1;
        n->is_static = $2;
        $$ = n;
    }
    ;

type_spec:
    INT                             { $$ = JTYPE_INT; }
    | DOUBLE                        { $$ = JTYPE_DOUBLE; }
    | FLOAT                         { $$ = JTYPE_FLOAT; }
    | LONG                          { $$ = JTYPE_LONG; }
    | CHAR                          { $$ = JTYPE_CHAR; }
    | BOOLEAN                       { $$ = JTYPE_BOOLEAN; }
    | STRING_TYPE                   { $$ = JTYPE_STRING; }
    | VOID                          { $$ = JTYPE_VOID; }
    | INT LBRACKET RBRACKET         { $$ = JTYPE_INT_ARRAY; }
    | DOUBLE LBRACKET RBRACKET      { $$ = JTYPE_DOUBLE_ARRAY; }
    | STRING_TYPE LBRACKET RBRACKET { $$ = JTYPE_STRING_ARRAY; }
    ;

opt_param_list:
    /* empty */                     { $$ = NULL; }
    | param_list                    { $$ = $1; }
    ;

param_list:
    typed_param {
        $$ = ast_new_stmt_list();
        ast_add_item($$, $1);
    }
    | param_list COMMA typed_param {
        ast_add_item($1, $3);
        $$ = $1;
    }
    ;

typed_param:
    type_spec IDENTIFIER {
        $$ = ast_new_typed_param($2, (JavaType)$1, yyline);
    }
    ;

statement_list:
    statement                       {
        $$ = ast_new_stmt_list();
        ast_add_item($$, $1);
    }
    | statement_list statement      {
        ast_add_item($1, $2);
        $$ = $1;
    }
    ;

statement:
    var_decl_stmt                   { $$ = $1; }
    | assign_stmt                   { $$ = $1; }
    | if_stmt                       { $$ = $1; }
    | while_stmt                    { $$ = $1; }
    | for_stmt                      { $$ = $1; }
    | return_stmt                   { $$ = $1; }
    | print_stmt                    { $$ = $1; }
    | expr_stmt                     { $$ = $1; }
    ;

var_decl_stmt:
    type_spec IDENTIFIER ASSIGN expression SEMICOLON {
        $$ = ast_new_var_decl($2, (JavaType)$1, $4, yyline);
    }
    | type_spec IDENTIFIER SEMICOLON {
        $$ = ast_new_var_decl($2, (JavaType)$1, NULL, yyline);
    }
    ;

assign_stmt:
    IDENTIFIER ASSIGN expression SEMICOLON {
        $$ = ast_new_assign($1, $3, yyline);
    }
    | IDENTIFIER PLUS_ASSIGN expression SEMICOLON {
        $$ = ast_new_assign($1,
            ast_new_binop(OP_ADD, ast_new_ident(strdup($1), yyline), $3, yyline),
            yyline);
    }
    | IDENTIFIER MINUS_ASSIGN expression SEMICOLON {
        $$ = ast_new_assign($1,
            ast_new_binop(OP_SUB, ast_new_ident(strdup($1), yyline), $3, yyline),
            yyline);
    }
    | IDENTIFIER TIMES_ASSIGN expression SEMICOLON {
        $$ = ast_new_assign($1,
            ast_new_binop(OP_MUL, ast_new_ident(strdup($1), yyline), $3, yyline),
            yyline);
    }
    | IDENTIFIER DIVIDE_ASSIGN expression SEMICOLON {
        $$ = ast_new_assign($1,
            ast_new_binop(OP_DIV, ast_new_ident(strdup($1), yyline), $3, yyline),
            yyline);
    }
    | IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression SEMICOLON {
        ASTNode *access = ast_new_array_access($1, $3, yyline);
        access->right = $6;
        $$ = ast_new_expr_stmt(access, yyline);
    }
    ;

if_stmt:
    IF LPAREN expression RPAREN block {
        $$ = ast_new_if($3, $5, NULL, yyline);
    }
    | IF LPAREN expression RPAREN block ELSE block {
        $$ = ast_new_if($3, $5, $7, yyline);
    }
    | IF LPAREN expression RPAREN block ELSE if_stmt {
        $$ = ast_new_if($3, $5, $7, yyline);
    }
    ;

block:
    LBRACE statement_list RBRACE    { $$ = $2; }
    | LBRACE RBRACE                 { $$ = ast_new_stmt_list(); }
    ;

while_stmt:
    WHILE LPAREN expression RPAREN block {
        $$ = ast_new_while($3, $5, yyline);
    }
    ;

for_stmt:
    FOR LPAREN for_init SEMICOLON expression SEMICOLON for_update RPAREN block {
        $$ = ast_new_for($3, $5, $7, $9, yyline);
    }
    ;

for_init:
    type_spec IDENTIFIER ASSIGN expression {
        $$ = ast_new_var_decl($2, (JavaType)$1, $4, yyline);
    }
    | IDENTIFIER ASSIGN expression {
        $$ = ast_new_assign($1, $3, yyline);
    }
    ;

for_update:
    IDENTIFIER INCREMENT {
        $$ = ast_new_assign($1,
            ast_new_binop(OP_ADD, ast_new_ident(strdup($1), yyline),
                ast_new_int_lit(1, yyline), yyline),
            yyline);
    }
    | IDENTIFIER DECREMENT {
        $$ = ast_new_assign($1,
            ast_new_binop(OP_SUB, ast_new_ident(strdup($1), yyline),
                ast_new_int_lit(1, yyline), yyline),
            yyline);
    }
    | INCREMENT IDENTIFIER {
        $$ = ast_new_assign($2,
            ast_new_binop(OP_ADD, ast_new_ident(strdup($2), yyline),
                ast_new_int_lit(1, yyline), yyline),
            yyline);
    }
    | IDENTIFIER ASSIGN expression {
        $$ = ast_new_assign($1, $3, yyline);
    }
    | IDENTIFIER PLUS_ASSIGN expression {
        $$ = ast_new_assign($1,
            ast_new_binop(OP_ADD, ast_new_ident(strdup($1), yyline), $3, yyline),
            yyline);
    }
    ;

return_stmt:
    RETURN expression SEMICOLON {
        $$ = ast_new_return($2, yyline);
    }
    | RETURN SEMICOLON {
        $$ = ast_new_return(NULL, yyline);
    }
    ;

print_stmt:
    SYSOUT_PRINTLN LPAREN expression RPAREN SEMICOLON {
        $$ = ast_new_print($3, yyline);
    }
    | SYSOUT_PRINTLN LPAREN RPAREN SEMICOLON {
        $$ = ast_new_print(ast_new_str_lit(strdup("\"\""), yyline), yyline);
    }
    | SYSOUT_PRINT LPAREN expression RPAREN SEMICOLON {
        $$ = ast_new_print($3, yyline);
    }
    ;

expr_stmt:
    expression SEMICOLON {
        $$ = ast_new_expr_stmt($1, yyline);
    }
    ;

opt_arg_list:
    /* empty */                     { $$ = NULL; }
    | arg_list                      { $$ = $1; }
    ;

arg_list:
    expression {
        $$ = ast_new_stmt_list();
        ast_add_item($$, $1);
    }
    | arg_list COMMA expression {
        ast_add_item($1, $3);
        $$ = $1;
    }
    ;

expression:
    expression PLUS expression      { $$ = ast_new_binop(OP_ADD, $1, $3, yyline); }
    | expression MINUS expression   { $$ = ast_new_binop(OP_SUB, $1, $3, yyline); }
    | expression TIMES expression   { $$ = ast_new_binop(OP_MUL, $1, $3, yyline); }
    | expression DIVIDE expression  { $$ = ast_new_binop(OP_DIV, $1, $3, yyline); }
    | expression MODULO expression  { $$ = ast_new_binop(OP_MOD, $1, $3, yyline); }
    | expression EQ expression      { $$ = ast_new_binop(OP_EQ, $1, $3, yyline); }
    | expression NEQ expression     { $$ = ast_new_binop(OP_NEQ, $1, $3, yyline); }
    | expression LT expression      { $$ = ast_new_binop(OP_LT, $1, $3, yyline); }
    | expression GT expression      { $$ = ast_new_binop(OP_GT, $1, $3, yyline); }
    | expression LTE expression     { $$ = ast_new_binop(OP_LTE, $1, $3, yyline); }
    | expression GTE expression     { $$ = ast_new_binop(OP_GTE, $1, $3, yyline); }
    | expression AND expression     { $$ = ast_new_binop(OP_AND, $1, $3, yyline); }
    | expression OR expression      { $$ = ast_new_binop(OP_OR, $1, $3, yyline); }
    | expression BITAND expression  { $$ = ast_new_binop(OP_BITAND, $1, $3, yyline); }
    | expression BITOR expression   { $$ = ast_new_binop(OP_BITOR, $1, $3, yyline); }
    | expression BITXOR expression  { $$ = ast_new_binop(OP_BITXOR, $1, $3, yyline); }
    | expression SHL expression     { $$ = ast_new_binop(OP_SHL, $1, $3, yyline); }
    | expression SHR expression     { $$ = ast_new_binop(OP_SHR, $1, $3, yyline); }
    | NOT expression                { $$ = ast_new_unaryop(OP_NOT, $2, yyline); }
    | BITNOT expression             { $$ = ast_new_unaryop(OP_BITNOT, $2, yyline); }
    | MINUS expression %prec UMINUS { $$ = ast_new_unaryop(OP_NEG, $2, yyline); }
    | postfix_expr                  { $$ = $1; }
    ;

postfix_expr:
    primary                         { $$ = $1; }
    | postfix_expr INCREMENT        { $$ = ast_new_unaryop(OP_INCREMENT, $1, yyline); }
    | postfix_expr DECREMENT        { $$ = ast_new_unaryop(OP_DECREMENT, $1, yyline); }
    ;

primary:
    INT_LITERAL                     { $$ = ast_new_int_lit($1, yyline); }
    | DOUBLE_LIT                    { $$ = ast_new_double_lit($1, yyline); }
    | STRING_LIT                    { $$ = ast_new_str_lit($1, yyline); }
    | CHAR_LIT                      { $$ = ast_new_char_lit($1, yyline); }
    | BOOL_LIT                      { $$ = ast_new_bool_lit($1, yyline); }
    | IDENTIFIER LPAREN opt_arg_list RPAREN {
        $$ = ast_new_func_call($1, $3, yyline);
    }
    | IDENTIFIER DOT IDENTIFIER LPAREN opt_arg_list RPAREN {
        $$ = ast_new_method_call($1, $3, $5, yyline);
    }
    | IDENTIFIER LBRACKET expression RBRACKET {
        $$ = ast_new_array_access($1, $3, yyline);
    }
    | NEW type_spec LBRACKET expression RBRACKET {
        $$ = ast_new_new_array((JavaType)$2, $4, yyline);
    }
    | LPAREN type_spec RPAREN primary {
        $$ = ast_new_cast((JavaType)$2, $4, yyline);
    }
    | IDENTIFIER                    { $$ = ast_new_ident($1, yyline); }
    | LPAREN expression RPAREN      { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error (line %d): %s near '%s'\n", yyline, s, yytext);
}
