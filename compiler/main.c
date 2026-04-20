#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"
#include "semantic.h"
#include "codegen.h"

extern FILE *yyin;
extern int yyparse(void);
extern ASTNode *ast_root;
int yyline = 1;

static void usage(const char *prog) {
    fprintf(stderr, "Usage: %s [options] <input-file>\n", prog);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  --target python|c   Target language (default: python)\n");
    fprintf(stderr, "  --json              Output everything as JSON\n");
    fprintf(stderr, "  --ast               Print AST\n");
    fprintf(stderr, "  --help              Show this help\n");
}

int main(int argc, char **argv) {
    const char *input_file = NULL;
    TargetLang target = TARGET_PYTHON;
    int json_mode = 0;
    int show_ast = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--target") == 0 && i + 1 < argc) {
            i++;
            if (strcmp(argv[i], "c") == 0) target = TARGET_C;
            else if (strcmp(argv[i], "python") == 0) target = TARGET_PYTHON;
            else {
                fprintf(stderr, "Unknown target: %s\n", argv[i]);
                return 1;
            }
        } else if (strcmp(argv[i], "--json") == 0) {
            json_mode = 1;
        } else if (strcmp(argv[i], "--ast") == 0) {
            show_ast = 1;
        } else if (strcmp(argv[i], "--help") == 0) {
            usage(argv[0]);
            return 0;
        } else {
            input_file = argv[i];
        }
    }

    if (!input_file) {
        usage(argv[0]);
        return 1;
    }

    yyin = fopen(input_file, "r");
    if (!yyin) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", input_file);
        return 1;
    }

    /* Parse */
    int parse_result = yyparse();
    fclose(yyin);

    if (parse_result != 0 || !ast_root) {
        if (json_mode) {
            printf("{\"success\":false,\"errors\":[{\"line\":0,\"message\":\"Parse failed\"}]}\n");
        }
        return 1;
    }

    /* Semantic analysis */
    SemanticResult *sem = semantic_analyze(ast_root);

    if (json_mode) {
        printf("{\"success\":%s,", sem->error_count == 0 ? "true" : "false");

        /* AST */
        printf("\"ast\":");
        ast_print_json(ast_root);

        /* Symbol table */
        printf(",\"symbols\":");
        symtab_print_json(sem->global_scope);

        /* Errors */
        printf(",\"errors\":");
        semantic_print_errors_json(sem);

        /* Generated code */
        if (sem->error_count == 0) {
            CodeGenResult *code = codegen_generate(ast_root, target);
            printf(",\"output\":\"");
            /* JSON-escape the output */
            const char *s = code->code;
            while (*s) {
                switch (*s) {
                    case '"':  printf("\\\""); break;
                    case '\\': printf("\\\\"); break;
                    case '\n': printf("\\n"); break;
                    case '\t': printf("\\t"); break;
                    default:   putchar(*s);
                }
                s++;
            }
            printf("\"");
            codegen_result_free(code);
        } else {
            printf(",\"output\":null");
        }
        printf("}\n");
    } else {
        /* Text mode */
        if (show_ast) {
            printf("=== AST ===\n");
            ast_print(ast_root, 0);
            printf("\n");
        }

        if (sem->error_count > 0) {
            semantic_print_errors(sem);
            semantic_result_free(sem);
            ast_free(ast_root);
            return 1;
        }

        CodeGenResult *code = codegen_generate(ast_root, target);
        printf("%s", code->code);
        codegen_result_free(code);
    }

    semantic_result_free(sem);
    ast_free(ast_root);
    return 0;
}
