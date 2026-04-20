#ifndef SYMTAB_H
#define SYMTAB_H

#include "ast.h"

typedef enum SymbolType {
    SYM_VARIABLE,
    SYM_FUNCTION,
    SYM_CLASS,
} SymbolType;

typedef struct Symbol {
    char *name;
    SymbolType type;
    JavaType java_type;
    int param_count;
    int line_declared;
    int is_static;
    AccessMod access;
    struct Symbol *next;
} Symbol;

#define SYMTAB_SIZE 211

typedef struct SymbolTable {
    Symbol *buckets[SYMTAB_SIZE];
    struct SymbolTable *parent;
} SymbolTable;

SymbolTable *symtab_create(SymbolTable *parent);
void symtab_destroy(SymbolTable *table);
Symbol *symtab_insert(SymbolTable *table, const char *name, SymbolType type,
                      JavaType java_type, int param_count, int line);
Symbol *symtab_lookup(SymbolTable *table, const char *name);
Symbol *symtab_lookup_local(SymbolTable *table, const char *name);
void symtab_print(SymbolTable *table);
void symtab_print_json(SymbolTable *table);

#endif
