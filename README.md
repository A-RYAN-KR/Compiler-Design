# TranspilerX — Java to C/Python Transpiler
## Complete Technical Documentation

---

## Table of Contents

1. [Project Overview](#1-project-overview)
2. [Architecture](#2-architecture)
3. [Directory Structure](#3-directory-structure)
4. [Compilation Pipeline Workflow](#4-compilation-pipeline-workflow)
5. [Phase 1 — Lexical Analysis](#5-phase-1--lexical-analysis)
6. [Phase 2 — Syntax Analysis Grammar](#6-phase-2--syntax-analysis-grammar)
7. [Syntax-Directed Definitions SDD](#7-syntax-directed-definitions-sdd)
8. [Syntax-Directed Translation SDT](#8-syntax-directed-translation-sdt)
9. [Semantic Rules and Actions](#9-semantic-rules-and-actions)
10. [Phase 4 — Code Generation](#10-phase-4--code-generation)
11. [AST Node Taxonomy](#11-ast-node-taxonomy)
12. [Frontend Architecture](#12-frontend-architecture)
13. [Backend API](#13-backend-api)

---

## 1. Project Overview

**TranspilerX** is a full-stack source-to-source compiler (transpiler) that accepts a subset of **Java** as input and produces equivalent code in either **C** or **Python**.

| Property | Value |
|---|---|
| Source language | Java (subset) |
| Target languages | C, Python |
| Compiler core | C + Flex (lexer) + Bison (LALR parser) |
| JS fallback | Node.js (mirrors C compiler pipeline) |
| Frontend | React + Vite + Monaco Editor |
| Backend API | Express.js (Node.js) |

### Supported Java Constructs

- `class` declarations with access modifiers (`public`, `private`, `protected`)
- Static methods with typed parameters — e.g. `public static int add(int a, int b)`
- Typed variable declarations — `int x = 10;`, `String s = "hello";`
- Control flow: `if / else if / else`, `while`, `for`
- `System.out.println()` / `System.out.print()`
- All arithmetic, relational, logical, and bitwise operators
- Compound assignment: `+=`, `-=`, `*=`, `/=`
- Postfix/prefix `++` / `--`
- Arrays — `int[]`, `new int[n]`, `arr[i]`
- Type casts — `(int) x`
- Method/function calls — `obj.method(args)`, `func(args)`

---

## 2. Architecture

```
┌─────────────────────────────────────────────────────────┐
│                    FRONTEND (React + Vite)               │
│  ┌─────────────────┐     ┌────────────────────────────┐  │
│  │  Monaco Editor  │     │   Output Panel (Tabs)      │  │
│  │  Java source    │     │  Output | Errors | Tokens  │  │
│  │  Syntax HL      │     │  AST    | Symbols          │  │
│  └─────────────────┘     └────────────────────────────┘  │
│              POST /transpile { code, target }             │
├─────────────────────────────────────────────────────────┤
│                  BACKEND (Express.js :3001)               │
│  Binary present? → C compiler (transpiler.exe --json)    │
│         else    → JS transpiler (transpiler.js)          │
├─────────────────────────────────────────────────────────┤
│              COMPILER CORE (C + Flex + Bison)            │
│                                                          │
│  Java Source                                             │
│     │                                                    │
│     ▼ lexer.l (Flex)                                     │
│  Token Stream                                            │
│     │                                                    │
│     ▼ parser.y (Bison LALR(1))                           │
│  Abstract Syntax Tree  (ast.h / ast.c)                   │
│     │                                                    │
│     ▼ semantic.c                                         │
│  Annotated AST + Symbol Table + Error List               │
│     │                                                    │
│     ▼ codegen.c                                          │
│  Generated C or Python Code                              │
└─────────────────────────────────────────────────────────┘
```

---

## 3. Directory Structure

```
transpiler-project/
├── compiler/
│   ├── lexer.l          Flex lexer  — Java tokenizer
│   ├── parser.y         Bison parser — Java grammar + SDD actions
│   ├── ast.h / ast.c    AST node types, constructors, JSON serialiser
│   ├── symtab.h/.c      Symbol table (scoped hash map)
│   ├── semantic.h/.c    Semantic analysis pass (tree walk)
│   ├── codegen.h/.c     Code generator  (Java → C / Python)
│   ├── main.c           CLI entry point, JSON output mode
│   └── Makefile         flex → bison → gcc build
│
├── backend/
│   ├── server.js        Express API (/transpile, /health)
│   └── transpiler.js    Pure-JS Java transpiler (fallback)
│
└── frontend/src/
    ├── App.jsx          Main UI component
    └── index.css        Dark-theme styles
```

---

## 4. Compilation Pipeline Workflow

```
Java Source Code
      │
      │  PHASE 1 — LEXICAL ANALYSIS  (lexer.l)
      ▼
  Flex scans characters; matches regex patterns;
  emits a token stream; tracks line numbers (yyline).
      │
      │  PHASE 2 — SYNTAX ANALYSIS   (parser.y)
      ▼
  Bison LALR(1) parser applies grammar productions.
  Executes SDD semantic actions on each reduction.
  Builds the Abstract Syntax Tree (AST).
      │
      │  PHASE 3 — SEMANTIC ANALYSIS (semantic.c)
      ▼
  Tree walk; scope management via SymbolTable stack;
  declaration / use-before-declare checks;
  type annotation on IDENT nodes.
      │
      │  PHASE 4 — CODE GENERATION   (codegen.c)
      ▼
  Second tree walk; target-specific emission;
  class unwrapping; Java → C/Python mappings.
      │
      │  PHASE 5 — JSON OUTPUT        (main.c --json)
      ▼
  { success, ast, symbols, errors, output }
      │
      │  PHASE 6 — UI DISPLAY         (frontend)
      ▼
  Output / Tokens / AST / Symbols / Errors tabs
```

---

## 5. Phase 1 — Lexical Analysis

### Token Classes

| Category | Tokens |
|---|---|
| Keywords | `class public private protected static void int double float long char boolean String if else while for return new true false null` |
| Special | `System.out.println`  `System.out.print` (each matched as ONE token) |
| Literals | `INT_LITERAL  DOUBLE_LIT  STRING_LIT  CHAR_LIT  BOOL_LIT` |
| Identifiers | `[a-zA-Z_][a-zA-Z0-9_]*` |
| Arithmetic | `PLUS MINUS TIMES DIVIDE MODULO` |
| Relational | `EQ NEQ LT GT LTE GTE` |
| Logical | `AND OR NOT` |
| Bitwise | `BITAND BITOR BITXOR BITNOT SHL SHR` |
| Increment | `INCREMENT DECREMENT` |
| Compound | `PLUS_ASSIGN MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN` |
| Delimiters | `LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET COMMA SEMICOLON DOT` |

### Key Regex Rules (lexer.l)

```lex
"System.out.println"         → SYSOUT_PRINTLN   (matched before identifiers)
"System.out.print"           → SYSOUT_PRINT

[a-zA-Z_][a-zA-Z0-9_]*      → keyword table lookup, else IDENTIFIER

[0-9]+\.[0-9]+([fFdD])?     → DOUBLE_LIT   (atof)
[0-9]+                       → INT_LITERAL  (atoi)
\"([^"\\]|\\.)*\"            → STRING_LIT   (strdup, keeps quotes)
\'([^'\\]|\\.)*\'            → CHAR_LIT     (yytext[1])

"++" "--" "==" "!=" "<=" ">=" "&&" "||"
"<<" ">>" "+=" "-=" "*=" "/="            → compound tokens (2-char first)

"//".*                        → skip (line comment)
"/*" ... "*/"                 → skip (block comment, count \n)
\n                            → yyline++
[ \t\r]+                      → skip whitespace
```

---

## 6. Phase 2 — Syntax Analysis Grammar

Parser is **LALR(1)** generated by Bison. Operator precedence (lowest → highest):

```
%left  OR                     logical or
%left  AND                    logical and
%left  BITOR                  bitwise or
%left  BITXOR                 bitwise xor
%left  BITAND                 bitwise and
%left  EQ  NEQ                equality
%left  LT  GT  LTE  GTE       relational
%left  SHL  SHR               shift
%left  PLUS  MINUS            additive
%left  TIMES  DIVIDE  MODULO  multiplicative
%right NOT  BITNOT            unary prefix
%right UMINUS                 unary minus (highest)
```

### Grammar (BNF)

```bnf
program       ::= class_list | statement_list

class_list    ::= class_decl | class_list class_decl

class_decl    ::= opt_access_mod class IDENTIFIER { class_body }

class_body    ::= class_member_list

class_member  ::= method_decl | field_decl

method_decl   ::= opt_access_mod opt_static type_spec IDENTIFIER
                  ( opt_param_list ) { statement_list }

field_decl    ::= opt_access_mod opt_static type_spec IDENTIFIER = expr ;
                | opt_access_mod opt_static type_spec IDENTIFIER ;

type_spec     ::= int | double | float | long | char | boolean
                | String | void | int[] | double[] | String[]

statement     ::= var_decl_stmt | assign_stmt | if_stmt | while_stmt
                | for_stmt | return_stmt | print_stmt | expr_stmt

var_decl_stmt ::= type_spec IDENTIFIER = expression ;
                | type_spec IDENTIFIER ;

assign_stmt   ::= IDENTIFIER = expression ;
                | IDENTIFIER OP= expression ;        (compound)
                | IDENTIFIER [ expression ] = expression ;

for_stmt      ::= for ( for_init ; expression ; for_update ) block

for_init      ::= type_spec IDENTIFIER = expression
                | IDENTIFIER = expression

for_update    ::= IDENTIFIER ++  |  IDENTIFIER --  |  ++ IDENTIFIER
                | IDENTIFIER = expression
                | IDENTIFIER += expression

print_stmt    ::= System.out.println ( expression ) ;
                | System.out.print   ( expression ) ;

expression    ::= expression BIN_OP expression
                | ! expression  |  ~ expression  |  - expression
                | postfix_expr

postfix_expr  ::= primary | postfix_expr ++ | postfix_expr --

primary       ::= literal
                | IDENTIFIER ( opt_arg_list )
                | IDENTIFIER . IDENTIFIER ( opt_arg_list )
                | IDENTIFIER [ expression ]
                | new type_spec [ expression ]
                | ( type_spec ) primary
                | IDENTIFIER
                | ( expression )
```

---

## 7. Syntax-Directed Definitions (SDD)

An **SDD** attaches synthesized attributes to every non-terminal. Here `$$` is always `ASTNode*` except for `type_spec` (returns `JavaType` enum) and `opt_access_mod` / `opt_static` (return `int`).

### Attribute Table

| Non-terminal | Attribute Type | Meaning |
|---|---|---|
| `program`, `class_list`, `statement_list` | `ASTNode*` | Root / list node |
| `class_decl`, `method_decl`, `field_decl` | `ASTNode*` | Declaration node |
| `statement`, `block`, `expr_stmt` | `ASTNode*` | Statement node |
| `expression`, `primary`, `postfix_expr` | `ASTNode*` | Expression node |
| `type_spec` | `int` (JavaType enum) | Java type constant |
| `opt_access_mod`, `access_mod` | `int` (AccessMod enum) | Access level |
| `opt_static` | `int` 0 or 1 | Static flag |
| `typed_param` | `ASTNode*` | Typed parameter node |
| `opt_param_list`, `param_list` | `ASTNode*` | Param list node |
| `opt_arg_list`, `arg_list` | `ASTNode*` | Arg list node |

### SDD Rules — Class & Method

| Production | Synthesized Attribute `$$` |
|---|---|
| `class_decl → [acc] class id { body }` | `ast_new_class_decl(id, acc, body, line)` |
| `opt_access_mod → ε` | `ACC_DEFAULT` |
| `opt_access_mod → public` | `ACC_PUBLIC` |
| `opt_access_mod → private` | `ACC_PRIVATE` |
| `opt_access_mod → protected` | `ACC_PROTECTED` |
| `opt_static → ε` | `0` |
| `opt_static → static` | `1` |
| `method_decl → [acc] [static] type id (params) {body}` | `ast_new_method_decl(id, type, acc, static, params, body, line)` |
| `field_decl → [acc] [static] type id = expr ;` | `n=ast_new_var_decl(id,type,expr,line); n→access=acc; n→is_static=static` |
| `typed_param → type id` | `ast_new_typed_param(id, type, line)` |

### SDD Rules — Type Specification

| Production | `$$` value |
|---|---|
| `type_spec → int` | `JTYPE_INT` |
| `type_spec → double` | `JTYPE_DOUBLE` |
| `type_spec → float` | `JTYPE_FLOAT` |
| `type_spec → long` | `JTYPE_LONG` |
| `type_spec → char` | `JTYPE_CHAR` |
| `type_spec → boolean` | `JTYPE_BOOLEAN` |
| `type_spec → String` | `JTYPE_STRING` |
| `type_spec → void` | `JTYPE_VOID` |
| `type_spec → int[]` | `JTYPE_INT_ARRAY` |
| `type_spec → double[]` | `JTYPE_DOUBLE_ARRAY` |
| `type_spec → String[]` | `JTYPE_STRING_ARRAY` |

### SDD Rules — Statements

| Production | `$$` |
|---|---|
| `var_decl → type id = expr ;` | `ast_new_var_decl(id, type, expr, line)` |
| `var_decl → type id ;` | `ast_new_var_decl(id, type, NULL, line)` |
| `assign → id = expr ;` | `ast_new_assign(id, expr, line)` |
| `assign → id += expr ;` | `ast_new_assign(id, BinOp(ADD, Ident(id), expr), line)` |
| `assign → id -= expr ;` | `ast_new_assign(id, BinOp(SUB, Ident(id), expr), line)` |
| `assign → id *= expr ;` | `ast_new_assign(id, BinOp(MUL, Ident(id), expr), line)` |
| `assign → id /= expr ;` | `ast_new_assign(id, BinOp(DIV, Ident(id), expr), line)` |
| `assign → id[e] = v ;` | `n=ArrayAccess(id,e); n→right=v; ExprStmt(n)` |
| `if → if(e) block` | `ast_new_if(e, block, NULL, line)` |
| `if → if(e) b1 else b2` | `ast_new_if(e, b1, b2, line)` |
| `if → if(e) b1 else if_stmt` | `ast_new_if(e, b1, if_stmt, line)` |
| `while → while(e) block` | `ast_new_while(e, block, line)` |
| `for → for(init;cond;upd) block` | `ast_new_for(init, cond, upd, block, line)` |
| `return → return expr ;` | `ast_new_return(expr, line)` |
| `return → return ;` | `ast_new_return(NULL, line)` |
| `print → System.out.println(e);` | `ast_new_print(e, line)` |
| `print → System.out.println();` | `ast_new_print(StrLit("\"\""), line)` |

### SDD Rules — For-Update (desugared)

| Production | `$$` desugaring |
|---|---|
| `for_update → id++` | `Assign(id, BinOp(ADD, Ident(id), IntLit(1)))` |
| `for_update → id--` | `Assign(id, BinOp(SUB, Ident(id), IntLit(1)))` |
| `for_update → ++id` | `Assign(id, BinOp(ADD, Ident(id), IntLit(1)))` |
| `for_update → id += e` | `Assign(id, BinOp(ADD, Ident(id), e))` |

### SDD Rules — Expressions

| Production | `$$` |
|---|---|
| `expr → expr + expr` | `ast_new_binop(OP_ADD, left, right, line)` |
| `expr → expr - expr` | `ast_new_binop(OP_SUB, ...)` |
| `expr → expr * expr` | `ast_new_binop(OP_MUL, ...)` |
| `expr → expr / expr` | `ast_new_binop(OP_DIV, ...)` |
| `expr → expr % expr` | `ast_new_binop(OP_MOD, ...)` |
| `expr → expr == expr` | `ast_new_binop(OP_EQ, ...)` |
| `expr → expr != expr` | `ast_new_binop(OP_NEQ, ...)` |
| `expr → expr < expr` | `ast_new_binop(OP_LT, ...)` |
| `expr → expr > expr` | `ast_new_binop(OP_GT, ...)` |
| `expr → expr <= expr` | `ast_new_binop(OP_LTE, ...)` |
| `expr → expr >= expr` | `ast_new_binop(OP_GTE, ...)` |
| `expr → expr && expr` | `ast_new_binop(OP_AND, ...)` |
| `expr → expr \|\| expr` | `ast_new_binop(OP_OR, ...)` |
| `expr → expr & expr` | `ast_new_binop(OP_BITAND, ...)` |
| `expr → expr \| expr` | `ast_new_binop(OP_BITOR, ...)` |
| `expr → expr ^ expr` | `ast_new_binop(OP_BITXOR, ...)` |
| `expr → expr << expr` | `ast_new_binop(OP_SHL, ...)` |
| `expr → expr >> expr` | `ast_new_binop(OP_SHR, ...)` |
| `expr → ! expr` | `ast_new_unaryop(OP_NOT, expr, line)` |
| `expr → ~ expr` | `ast_new_unaryop(OP_BITNOT, expr, line)` |
| `expr → - expr` | `ast_new_unaryop(OP_NEG, expr, line)` |
| `postfix → postfix++` | `ast_new_unaryop(OP_INCREMENT, expr, line)` |
| `postfix → postfix--` | `ast_new_unaryop(OP_DECREMENT, expr, line)` |

### SDD Rules — Primary

| Production | `$$` |
|---|---|
| `primary → INT_LITERAL` | `ast_new_int_lit(ival, line)` |
| `primary → DOUBLE_LIT` | `ast_new_double_lit(dval, line)` |
| `primary → STRING_LIT` | `ast_new_str_lit(sval, line)` |
| `primary → CHAR_LIT` | `ast_new_char_lit(cval, line)` |
| `primary → BOOL_LIT` | `ast_new_bool_lit(bval, line)` |
| `primary → id(args)` | `ast_new_func_call(id, args, line)` |
| `primary → id.id(args)` | `ast_new_method_call(obj, method, args, line)` |
| `primary → id[expr]` | `ast_new_array_access(id, expr, line)` |
| `primary → new type[expr]` | `ast_new_new_array(type, size, line)` |
| `primary → (type) primary` | `ast_new_cast(type, expr, line)` |
| `primary → IDENTIFIER` | `ast_new_ident(name, line)` |
| `primary → (expr)` | `expr` (passthrough) |

---

## 8. Syntax-Directed Translation (SDT)

An **SDT** embeds semantic actions *inside* productions. Bison fires each action when the production is **reduced**. The key translations in our system are shown below with the action code.

### SDT Scheme — Class Declaration

```yacc
class_decl:
    opt_access_mod CLASS IDENTIFIER LBRACE class_body RBRACE
    {
        /* Action fires AFTER reducing the full class body.
           $1 = AccessMod enum value
           $3 = char* (identifier, strdup'd by lexer)
           $5 = ASTNode* (stmt list of members)           */
        $$ = ast_new_class_decl($3, (AccessMod)$1, $5, yyline);
    }
```

### SDT Scheme — Method Declaration

```yacc
method_decl:
    opt_access_mod opt_static type_spec IDENTIFIER
    LPAREN opt_param_list RPAREN
    LBRACE statement_list RBRACE
    {
        /* $1=AccessMod  $2=is_static(0/1)  $3=JavaType
           $4=name       $6=params          $9=body       */
        $$ = ast_new_method_decl($4, (JavaType)$3,
                 (AccessMod)$1, $2, $6, $9, yyline);
    }
```

### SDT Scheme — Compound Assignment Desugaring

```yacc
assign_stmt:
    IDENTIFIER PLUS_ASSIGN expression SEMICOLON
    {
        /*  id += e  is translated inline to  id = id + e
            A fresh Ident node is created for the LHS of BinOp
            so the tree does not share pointers.             */
        $$ = ast_new_assign($1,
            ast_new_binop(OP_ADD,
                ast_new_ident(strdup($1), yyline),   /* fresh copy */
                $3, yyline),
            yyline);
    }
```

### SDT Scheme — For-Update (i++ → assignment)

```yacc
for_update:
    IDENTIFIER INCREMENT
    {
        /* i++  becomes  i = i + 1  (structurally)
           This normalises all loop updates to assignments
           so the code generator handles a single AST form. */
        $$ = ast_new_assign($1,
            ast_new_binop(OP_ADD,
                ast_new_ident(strdup($1), yyline),
                ast_new_int_lit(1, yyline),
                yyline),
            yyline);
    }
```

### SDT Scheme — Array Slot Assignment

```yacc
assign_stmt:
    IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression SEMICOLON
    {
        /* arr[i] = val
           ArrayAccess node reuses its `right` field for the value
           when used as an LHS. Wrapped in ExprStmt.           */
        ASTNode *access = ast_new_array_access($1, $3, yyline);
        access->right   = $6;
        $$ = ast_new_expr_stmt(access, yyline);
    }
```

### SDT Scheme — Statement List (growing list)

```yacc
statement_list:
    statement
    {
        $$ = ast_new_stmt_list();   /* allocate new list */
        ast_add_item($$, $1);       /* add first item    */
    }
  | statement_list statement
    {
        ast_add_item($1, $2);       /* grow existing list */
        $$ = $1;                    /* propagate same ptr */
    }
```

### SDT Scheme — Print Statement

```yacc
print_stmt:
    SYSOUT_PRINTLN LPAREN expression RPAREN SEMICOLON
    {
        /* Generic print node — target (printf vs print)
           is decided during code generation, not here.  */
        $$ = ast_new_print($3, yyline);
    }
  | SYSOUT_PRINTLN LPAREN RPAREN SEMICOLON
    {
        /* println() with no args → print empty string   */
        $$ = ast_new_print(
            ast_new_str_lit(strdup("\"\""), yyline), yyline);
    }
```

---

## 9. Semantic Rules and Actions

The semantic phase is a **post-parse depth-first tree walk** in `semantic.c`. It uses a **linked chain of hash-map scopes** (`SymbolTable`) to track all identifiers.

### 9.1 Symbol Table Layout

```c
typedef struct Symbol {
    char       *name;           /* identifier name (heap)        */
    SymbolType  type;           /* SYM_VARIABLE | SYM_FUNCTION
                                   | SYM_CLASS                   */
    JavaType    java_type;      /* JTYPE_INT, JTYPE_STRING, ...  */
    int         param_count;    /* number of params (functions)  */
    int         line_declared;  /* for error messages            */
    int         is_static;      /* static flag                   */
    AccessMod   access;         /* public/private/protected      */
    struct Symbol *next;        /* hash chain (separate chaining)*/
} Symbol;

typedef struct SymbolTable {
    Symbol      *buckets[211];  /* djb2 hash, 211 buckets        */
    SymbolTable *parent;        /* enclosing scope               */
} SymbolTable;
```

**Lookup** chains through `parent` pointers until a match is found or the global scope is exhausted.

### 9.2 Scope Management

| Event | Action |
|---|---|
| Program start | Create global `SymbolTable`; set `current_scope = global` |
| Enter `ClassDecl` | `push(new SymbolTable(parent=current_scope))` |
| Exit `ClassDecl` | `pop(); destroy class scope` |
| Enter `MethodDecl` | `push(new SymbolTable(parent=class_scope))` |
| Insert each parameter | `symtab_insert(method_scope, param.name, SYM_VARIABLE, param.java_type, ...)` |
| Exit `MethodDecl` | `pop(); destroy method scope` |
| Enter/Exit `block` | *(no extra scope — Java block scoping simplified to method scope)* |

### 9.3 Semantic Rules (Formal Specification)

#### SR-1 — No Duplicate Class Declaration

```
WHERE   : node.type == CLASS_DECL
PRE     : symtab_lookup_local(current_scope, node.name) == NULL
ACTION  : symtab_insert(current_scope, node.name, SYM_CLASS,
                        JTYPE_UNKNOWN, 0, node.line)
ERROR   : "Class 'X' already declared (line N)"
```

#### SR-2 — No Duplicate Method

```
WHERE   : node.type == METHOD_DECL
PRE     : symtab_lookup_local(current_scope, node.name) == NULL
ACTION  : sym = symtab_insert(scope, name, SYM_FUNCTION,
                              returnType, paramCount, line)
          sym→is_static = node.is_static
          sym→access    = node.access
ERROR   : "Method 'X' already declared (line N)"
```

#### SR-3 — No Duplicate Variable in Same Scope

```
WHERE   : node.type == VAR_DECL
PRE     : symtab_lookup_local(current_scope, node.name) == NULL
ACTION  : sym = symtab_insert(scope, name, SYM_VARIABLE,
                              node.java_type, 0, line)
ERROR   : "Variable 'X' already declared in this scope (line N)"
```

#### SR-4 — Variable Must Be Declared Before Use

```
WHERE   : node.type == IDENT  (inside any expression)
PRE     : symtab_lookup(current_scope, node.name) != NULL
ACTION  : node→java_type = sym→java_type   ← TYPE ANNOTATION
ERROR   : "Undeclared identifier 'X'"
```

#### SR-5 — Assignment Target Must Exist and Not Be a Function

```
WHERE   : node.type == ASSIGN
CHECK 1 : symtab_lookup(scope, node.name) != NULL
CHECK 2 : sym→type != SYM_FUNCTION
ERROR 1 : "Undeclared variable 'X'"
ERROR 2 : "Cannot assign to method 'X'"
```

#### SR-6 — Function Call Arity and Name Check

```
WHERE   : node.type == FUNC_CALL
CHECK 1 : symtab_lookup(scope, node.name) != NULL
CHECK 2 : sym→type == SYM_FUNCTION
CHECK 3 : actual_arg_count == sym→param_count
ERROR 1 : "Undeclared method 'X'"
ERROR 2 : "'X' is not a method"
ERROR 3 : "Method 'X' expects N arguments, got M"
```

#### SR-7 — Array Must Be Declared Before Subscript

```
WHERE   : node.type == ARRAY_ACCESS
CHECK   : symtab_lookup(scope, node.name) != NULL
ERROR   : "Undeclared array 'X'"
```

#### SR-8 — Method Calls on Objects (open-world)

```
WHERE   : node.type == METHOD_CALL
ACTION  : Recursively analyse all arguments; NO object lookup
REASON  : Library / runtime types cannot be resolved at compile time
```

### 9.4 Type Annotation

SR-4 propagates the declared type from the symbol table onto every `NODE_IDENT` node:

```c
case NODE_IDENT: {
    Symbol *sym = symtab_lookup(current_scope, node->name);
    if (!sym) {
        add_error(node->line, "Undeclared identifier '%s'", node->name);
    } else {
        node->java_type = sym->java_type;  /* annotation */
    }
}
```

The code generator later reads `java_type` to choose the correct `printf` format specifier.

### 9.5 Error Strategy

Errors are **non-fatal**. The analyser collects up to `MAX_ERRORS = 100` and continues walking the tree, so all errors in a file are reported in one pass. Code generation is **blocked** when `error_count > 0`.

```c
typedef struct SemanticResult {
    SemanticError errors[MAX_ERRORS];   /* {line, message[256]} */
    int           error_count;
    SymbolTable  *global_scope;         /* used for JSON /symbols export */
} SemanticResult;
```

---

## 10. Phase 4 — Code Generation

### 10.1 Java Type → C Type

| Java | C |
|---|---|
| `int` | `int` |
| `long` | `long` |
| `double` | `double` |
| `float` | `float` |
| `char` | `char` |
| `boolean` | `int` (C has no native bool) |
| `String` | `const char*` |
| `void` | `void` |
| `int[]` | `int*` |
| `double[]` | `double*` |
| `String[]` | `const char**` |

### 10.2 Java Type → Python Hint

| Java | Python |
|---|---|
| `int`, `long` | `int` |
| `double`, `float` | `float` |
| `char` | `str` |
| `boolean` | `bool` |
| `String` | `str` |
| Arrays | `list` |

### 10.3 printf Format Specifier (C target)

Inferred from `infer_type(expr_node)` which reads `java_type`:

| Java Type | Format |
|---|---|
| `int`, `boolean` | `%d` |
| `long` | `%ld` |
| `double`, `float` | `%f` |
| `char` | `%c` |
| `String` | `%s` |

### 10.4 Control Flow Translation

| Java | C output | Python output |
|---|---|---|
| `if (c) { }` | `if (c) { }` | `if c:` |
| `else if (c) { }` | `else if (c) { }` | `elif c:` |
| `else { }` | `else { }` | `else:` |
| `while (c) { }` | `while (c) { }` | `while c:` |
| `for (int i=0; i<n; i++) {}` | `for (int i=0; (i<n); i=(i+1)) {}` | `i=0` → `while (i<n):` → `i=(i+1)` |

> **Python for-loop:** Java's C-style `for` has no direct Python equivalent. The transpiler emits an init statement followed by a `while` loop and appends the update at the end of the body.

### 10.5 Literal and Keyword Translation

| Java | C | Python |
|---|---|---|
| `true` | `1` | `True` |
| `false` | `0` | `False` |
| `null` | `NULL` | `None` |
| `new int[n]` | `(int*)calloc(n, sizeof(int))` | `[0] * n` |
| `(double) x` | `(double)(x)` | `float(x)` |
| `(int) x` | `(int)(x)` | `int(x)` |

### 10.6 logical Operator Translation

| Java | C | Python |
|---|---|---|
| `&&` | `&&` | `and` |
| `\|\|` | `\|\|` | `or` |
| `!` | `!` | `not ` |

### 10.7 Class Unwrapping (Java → C)

Java classes are **structural containers** — they become flat functions in C.

```
ALGORITHM:
1. For each ClassDecl in AST:
   a. First pass  → emit non-main static methods as C functions
   b. Static fields → global variable declarations
   c. Second pass → emit main() with signature:
                    void main(int argc, char *argv[])
                    + inject  return 0;  at end
2. Non-class (loose) statements → wrap in   int main() { ... }
```

**Example:**

```java
public class Calc {
    public static int add(int a, int b) { return a + b; }
    public static void main(String[] args) {
        System.out.println(add(1, 2));
    }
}
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add(int a, int b) {
    return (a + b);
}

void main(int argc, char *argv[]) {
    printf("%d\n", add(1, 2));
    return 0;
}
```

```python
def add(a, b):
    return (a + b)

def main():
    print(add(1, 2))

if __name__ == "__main__":
    main()
```

---

## 11. AST Node Taxonomy

### Complete Node Type Table

| Node Type | Key Fields | Description |
|---|---|---|
| `NODE_PROGRAM` | `items[]` | Top-level list |
| `NODE_STMT_LIST` | `items[]`, `item_count` | Generic node list |
| `NODE_CLASS_DECL` | `name`, `access`, `body` | Java class |
| `NODE_METHOD_DECL` | `name`, `java_type`, `access`, `is_static`, `left`(params), `body` | Java method |
| `NODE_VAR_DECL` | `name`, `java_type`, `access`, `is_static`, `left`(init) | Typed variable declaration |
| `NODE_ASSIGN` | `name`, `left`(value) | Assignment |
| `NODE_IF` | `left`(cond), `body`(then), `right`(else or elif) | Conditional |
| `NODE_WHILE` | `left`(cond), `body` | While loop |
| `NODE_FOR` | `init`, `left`(cond), `update`, `body` | For loop |
| `NODE_RETURN` | `left`(expr or NULL) | Return |
| `NODE_PRINT` | `left`(expr) | System.out.println |
| `NODE_EXPR_STMT` | `left`(expr) | Expression as statement |
| `NODE_BINOP` | `op`, `left`, `right` | Binary operation |
| `NODE_UNARYOP` | `op`, `left` | Unary operation |
| `NODE_INT_LIT` | `int_val` | Integer literal |
| `NODE_DOUBLE_LIT` | `num_val` | Double literal |
| `NODE_STR_LIT` | `name` (with `"`) | String literal |
| `NODE_CHAR_LIT` | `int_val` (char as int) | Char literal |
| `NODE_BOOL_LIT` | `int_val` (0 or 1) | Boolean literal |
| `NODE_IDENT` | `name`, `java_type` (annotated) | Identifier |
| `NODE_FUNC_CALL` | `name`, `left`(args) | Function call |
| `NODE_METHOD_CALL` | `name` ("obj.method"), `left`(args) | Method call |
| `NODE_ARRAY_ACCESS` | `name`, `left`(index), `right`(value if LHS) | Array subscript |
| `NODE_NEW_ARRAY` | `java_type`, `left`(size) | Array allocation |
| `NODE_CAST` | `java_type`, `left`(expr) | Type cast |
| `NODE_TYPED_PARAM` | `name`, `java_type` | Method parameter |

### AST Example — `int x = add(a, b);`

```
VarDecl  name="x"  javaType=JTYPE_INT
  └─ left: FuncCall  name="add"
             └─ left: StmtList (args)
                  ├─ [0] Identifier  name="a"  javaType=JTYPE_INT
                  └─ [1] Identifier  name="b"  javaType=JTYPE_INT
```

### AST Example — `for (int i = 0; i < n; i++) { ... }`

```
For
 ├─ init:   VarDecl  name="i"  javaType=JTYPE_INT
 │            └─ left: IntLit  value=0
 │
 ├─ left:   BinOp  op=OP_LT
 │            ├─ left:  Identifier  name="i"
 │            └─ right: Identifier  name="n"
 │
 ├─ update: Assign  name="i"
 │            └─ left: BinOp  op=OP_ADD
 │                      ├─ left:  Identifier  name="i"
 │                      └─ right: IntLit  value=1
 │
 └─ body:   StmtList
              └─ ...
```

### AST Example — `if (x > 0) { ... } else { ... }`

```
If
 ├─ left (cond):  BinOp  op=OP_GT
 │                  ├─ Identifier  name="x"
 │                  └─ IntLit  value=0
 ├─ body (then):  StmtList  [...]
 └─ right (else): StmtList  [...]
```

---

## 12. Frontend Architecture

```
App.jsx
 ├── State
 │    ├── code       Java source string
 │    ├── target     "python" | "c"
 │    ├── result     { success, tokens, ast, symbols, errors, output }
 │    ├── loading    boolean
 │    └── activeTab  "output"|"errors"|"tokens"|"ast"|"symbols"
 │
 ├── handleTranspile()
 │    └── POST /transpile { code, target }
 │         sets result state; switches to output or errors tab
 │
 ├── Monaco Editor
 │    └── defaultLanguage = "java"   (full Java syntax highlighting)
 │         fontFamily     = JetBrains Mono
 │         features: bracket-pair coloring, smooth caret, line highlight
 │
 ├── ASTTreeView  (recursive component)
 │    ├── node.type          → cyan label
 │    ├── node.name          → orange text
 │    ├── node.javaType      → small orange annotation  ": int"
 │    ├── node.value         → green (literals)
 │    ├── node.op            → red (operators)
 │    └── recurses into: left, right, body, init, update, items[]
 │
 └── Tabs
      ├── Output   monospace generated code
      ├── Errors   line number + message list
      ├── Tokens   grid: type | value | line
      ├── AST      recursive ASTTreeView
      └── Symbols  table: Name | Kind | Java Type | Params | Line
```

---

## 13. Backend API

### `POST /transpile`

**Request body:**
```json
{ "code": "public class Hello { ... }", "target": "python" }
```

**Success response:**
```json
{
  "success": true,
  "tokens": [
    { "type": "CLASS", "value": "class", "line": 1 }
  ],
  "ast": {
    "type": "Program",
    "items": [{ "type": "ClassDecl", "name": "Hello", "..." : "..." }]
  },
  "symbols": [
    { "name": "Hello", "type": "class", "javaType": "class",
      "params": 0, "line": 1 }
  ],
  "errors": [],
  "output": "class Hello:\n    def main():\n        ...\n"
}
```

**Failure response:**
```json
{
  "success": false,
  "errors": [{ "line": 3, "message": "Undeclared identifier 'x'" }],
  "output": null
}
```

### `GET /health`

```json
{ "status": "ok", "mode": "javascript" }
```

### Binary vs JS Fallback Logic

```
POST /transpile arrives
       │
       ▼
compiler/transpiler.exe  exists?
       │
      YES ─────────────────────────────────▶ execFile(binary,
       │                                      ["--json","--target",target,
       │                                        tmpfile])
       │                                     parse stdout as JSON
      NO
       │
       ▼
require('./transpiler.js')
transpile(code, target)
       │
       ▼
JSON response to frontend
```

---

*TranspilerX — Java to C/Python Transpiler*
*Stack: Flex + Bison + C | Express.js | React + Monaco Editor*
