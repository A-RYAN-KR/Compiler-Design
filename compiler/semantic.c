#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

static SemanticResult *result;
static SymbolTable *current_scope;

static void add_error(int line, const char *fmt, ...) {
    if (result->error_count >= MAX_ERRORS) return;
    SemanticError *err = &result->errors[result->error_count++];
    err->line = line;
    va_list args;
    va_start(args, fmt);
    vsnprintf(err->message, sizeof(err->message), fmt, args);
    va_end(args);
}

static void analyze_node(ASTNode *node);

static void analyze_expr(ASTNode *node) {
    if (!node) return;
    switch (node->type) {
        case NODE_INT_LIT:
        case NODE_DOUBLE_LIT:
        case NODE_STR_LIT:
        case NODE_CHAR_LIT:
        case NODE_BOOL_LIT:
            break;
        case NODE_IDENT: {
            Symbol *sym = symtab_lookup(current_scope, node->name);
            if (!sym) {
                add_error(node->line, "Undeclared identifier '%s'", node->name);
            } else {
                node->java_type = sym->java_type;
            }
            break;
        }
        case NODE_BINOP:
            analyze_expr(node->left);
            analyze_expr(node->right);
            break;
        case NODE_UNARYOP:
            analyze_expr(node->left);
            break;
        case NODE_FUNC_CALL: {
            Symbol *sym = symtab_lookup(current_scope, node->name);
            if (!sym) {
                add_error(node->line, "Undeclared method '%s'", node->name);
            } else if (sym->type != SYM_FUNCTION) {
                add_error(node->line, "'%s' is not a method", node->name);
            } else {
                int arg_count = node->left ? node->left->item_count : 0;
                if (arg_count != sym->param_count) {
                    add_error(node->line,
                        "Method '%s' expects %d arguments, got %d",
                        node->name, sym->param_count, arg_count);
                }
            }
            if (node->left) {
                for (int i = 0; i < node->left->item_count; i++)
                    analyze_expr(node->left->items[i]);
            }
            break;
        }
        case NODE_METHOD_CALL: {
            /* For System.out.println etc, we don't require lookup */
            if (node->left) {
                for (int i = 0; i < node->left->item_count; i++)
                    analyze_expr(node->left->items[i]);
            }
            break;
        }
        case NODE_ARRAY_ACCESS: {
            Symbol *sym = symtab_lookup(current_scope, node->name);
            if (!sym) {
                add_error(node->line, "Undeclared array '%s'", node->name);
            }
            analyze_expr(node->left);
            break;
        }
        case NODE_NEW_ARRAY:
            analyze_expr(node->left);
            break;
        case NODE_CAST:
            analyze_expr(node->left);
            break;
        default:
            break;
    }
}

static void analyze_node(ASTNode *node) {
    if (!node) return;
    switch (node->type) {
        case NODE_PROGRAM:
        case NODE_STMT_LIST:
            for (int i = 0; i < node->item_count; i++)
                analyze_node(node->items[i]);
            break;
        case NODE_CLASS_DECL: {
            Symbol *existing = symtab_lookup_local(current_scope, node->name);
            if (existing) {
                add_error(node->line, "Class '%s' already declared (line %d)",
                    node->name, existing->line_declared);
            } else {
                symtab_insert(current_scope, node->name, SYM_CLASS,
                    JTYPE_UNKNOWN, 0, node->line);
            }
            SymbolTable *class_scope = symtab_create(current_scope);
            SymbolTable *prev = current_scope;
            current_scope = class_scope;
            analyze_node(node->body);
            current_scope = prev;
            symtab_destroy(class_scope);
            break;
        }
        case NODE_PRINT:
            analyze_expr(node->left);
            break;
        case NODE_VAR_DECL: {
            Symbol *existing = symtab_lookup_local(current_scope, node->name);
            if (existing) {
                add_error(node->line, "Variable '%s' already declared in this scope (line %d)",
                    node->name, existing->line_declared);
            } else {
                Symbol *sym = symtab_insert(current_scope, node->name, SYM_VARIABLE,
                    node->java_type, 0, node->line);
                sym->is_static = node->is_static;
                sym->access = node->access;
            }
            if (node->left) analyze_expr(node->left);
            break;
        }
        case NODE_ASSIGN: {
            Symbol *sym = symtab_lookup(current_scope, node->name);
            if (!sym) {
                add_error(node->line, "Undeclared variable '%s'", node->name);
            } else if (sym->type == SYM_FUNCTION) {
                add_error(node->line, "Cannot assign to method '%s'", node->name);
            }
            analyze_expr(node->left);
            break;
        }
        case NODE_METHOD_DECL: {
            Symbol *existing = symtab_lookup_local(current_scope, node->name);
            if (existing) {
                add_error(node->line, "Method '%s' already declared (line %d)",
                    node->name, existing->line_declared);
            }
            int param_count = node->left ? node->left->item_count : 0;
            Symbol *sym = symtab_insert(current_scope, node->name, SYM_FUNCTION,
                node->java_type, param_count, node->line);
            sym->is_static = node->is_static;
            sym->access = node->access;

            SymbolTable *method_scope = symtab_create(current_scope);
            SymbolTable *prev = current_scope;
            current_scope = method_scope;

            if (node->left) {
                for (int i = 0; i < node->left->item_count; i++) {
                    ASTNode *param = node->left->items[i];
                    symtab_insert(current_scope, param->name, SYM_VARIABLE,
                        param->java_type, 0, param->line);
                }
            }
            analyze_node(node->body);
            current_scope = prev;
            symtab_destroy(method_scope);
            break;
        }
        case NODE_IF:
            analyze_expr(node->left);
            analyze_node(node->body);
            if (node->right) analyze_node(node->right);
            break;
        case NODE_WHILE:
            analyze_expr(node->left);
            analyze_node(node->body);
            break;
        case NODE_FOR:
            if (node->init) analyze_node(node->init);
            analyze_expr(node->left);
            if (node->update) analyze_node(node->update);
            analyze_node(node->body);
            break;
        case NODE_RETURN:
            if (node->left) analyze_expr(node->left);
            break;
        case NODE_EXPR_STMT:
            analyze_expr(node->left);
            break;
        default:
            break;
    }
}

SemanticResult *semantic_analyze(ASTNode *root) {
    result = (SemanticResult *)calloc(1, sizeof(SemanticResult));
    result->global_scope = symtab_create(NULL);
    current_scope = result->global_scope;
    analyze_node(root);
    return result;
}

void semantic_result_free(SemanticResult *r) {
    if (!r) return;
    symtab_destroy(r->global_scope);
    free(r);
}

void semantic_print_errors(SemanticResult *r) {
    for (int i = 0; i < r->error_count; i++) {
        fprintf(stderr, "Semantic Error (line %d): %s\n",
            r->errors[i].line, r->errors[i].message);
    }
}

void semantic_print_errors_json(SemanticResult *r) {
    printf("[");
    for (int i = 0; i < r->error_count; i++) {
        if (i > 0) printf(",");
        printf("{\"line\":%d,\"message\":\"", r->errors[i].line);
        const char *s = r->errors[i].message;
        while (*s) {
            if (*s == '"') printf("\\\"");
            else if (*s == '\\') printf("\\\\");
            else putchar(*s);
            s++;
        }
        printf("\"}");
    }
    printf("]");
}
