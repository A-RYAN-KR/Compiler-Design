#include "symtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int hash(const char *s) {
    unsigned int h = 5381;
    while (*s) h = ((h << 5) + h) + (unsigned char)*s++;
    return h % SYMTAB_SIZE;
}

SymbolTable *symtab_create(SymbolTable *parent) {
    SymbolTable *table = (SymbolTable *)calloc(1, sizeof(SymbolTable));
    table->parent = parent;
    return table;
}

void symtab_destroy(SymbolTable *table) {
    if (!table) return;
    for (int i = 0; i < SYMTAB_SIZE; i++) {
        Symbol *sym = table->buckets[i];
        while (sym) {
            Symbol *next = sym->next;
            free(sym->name);
            free(sym);
            sym = next;
        }
    }
    free(table);
}

Symbol *symtab_insert(SymbolTable *table, const char *name, SymbolType type,
                      JavaType java_type, int param_count, int line) {
    unsigned int idx = hash(name);
    Symbol *sym = (Symbol *)malloc(sizeof(Symbol));
    sym->name = strdup(name);
    sym->type = type;
    sym->java_type = java_type;
    sym->param_count = param_count;
    sym->line_declared = line;
    sym->is_static = 0;
    sym->access = ACC_DEFAULT;
    sym->next = table->buckets[idx];
    table->buckets[idx] = sym;
    return sym;
}

Symbol *symtab_lookup(SymbolTable *table, const char *name) {
    while (table) {
        Symbol *found = symtab_lookup_local(table, name);
        if (found) return found;
        table = table->parent;
    }
    return NULL;
}

Symbol *symtab_lookup_local(SymbolTable *table, const char *name) {
    unsigned int idx = hash(name);
    Symbol *sym = table->buckets[idx];
    while (sym) {
        if (strcmp(sym->name, name) == 0) return sym;
        sym = sym->next;
    }
    return NULL;
}

static const char *sym_type_name(SymbolType t) {
    switch (t) {
        case SYM_FUNCTION: return "function";
        case SYM_VARIABLE: return "variable";
        case SYM_CLASS:    return "class";
        default:           return "unknown";
    }
}

void symtab_print(SymbolTable *table) {
    printf("%-20s %-12s %-12s %-8s %-6s\n", "Name", "Kind", "Type", "Params", "Line");
    printf("%-20s %-12s %-12s %-8s %-6s\n", "----", "----", "----", "------", "----");
    for (int i = 0; i < SYMTAB_SIZE; i++) {
        Symbol *sym = table->buckets[i];
        while (sym) {
            printf("%-20s %-12s %-12s %-8d %-6d\n",
                sym->name,
                sym_type_name(sym->type),
                java_type_str(sym->java_type),
                sym->param_count,
                sym->line_declared);
            sym = sym->next;
        }
    }
}

void symtab_print_json(SymbolTable *table) {
    printf("[");
    int first = 1;
    for (int i = 0; i < SYMTAB_SIZE; i++) {
        Symbol *sym = table->buckets[i];
        while (sym) {
            if (!first) printf(",");
            printf("{\"name\":\"%s\",\"type\":\"%s\",\"javaType\":\"%s\",\"params\":%d,\"line\":%d}",
                sym->name,
                sym_type_name(sym->type),
                java_type_str(sym->java_type),
                sym->param_count,
                sym->line_declared);
            first = 0;
            sym = sym->next;
        }
    }
    printf("]");
}
