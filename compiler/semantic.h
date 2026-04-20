#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "symtab.h"

#define MAX_ERRORS 100

typedef struct SemanticError {
    char message[256];
    int line;
} SemanticError;

typedef struct SemanticResult {
    SemanticError errors[MAX_ERRORS];
    int error_count;
    SymbolTable *global_scope;
} SemanticResult;

SemanticResult *semantic_analyze(ASTNode *root);
void semantic_result_free(SemanticResult *result);
void semantic_print_errors(SemanticResult *result);
void semantic_print_errors_json(SemanticResult *result);

#endif
