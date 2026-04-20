#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"

typedef enum TargetLang {
    TARGET_PYTHON,
    TARGET_C,
} TargetLang;

typedef struct CodeGenResult {
    char *code;
    int code_len;
    int code_capacity;
} CodeGenResult;

CodeGenResult *codegen_generate(ASTNode *root, TargetLang target);
void codegen_result_free(CodeGenResult *result);

#endif
