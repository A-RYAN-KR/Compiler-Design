#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

static CodeGenResult *res;
static TargetLang target;
static int indent_level;

static void emit(const char *fmt, ...) {
    char buf[2048];
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    while (res->code_len + len + 1 >= res->code_capacity) {
        res->code_capacity *= 2;
        res->code = (char *)realloc(res->code, res->code_capacity);
    }
    memcpy(res->code + res->code_len, buf, len);
    res->code_len += len;
    res->code[res->code_len] = '\0';
}

static void emit_indent(void) {
    for (int i = 0; i < indent_level; i++) {
        emit("    ");
    }
}

/* Map Java types to C types */
static const char *c_type_str(JavaType jtype) {
    switch (jtype) {
        case JTYPE_VOID:    return "void";
        case JTYPE_INT:     return "int";
        case JTYPE_DOUBLE:  return "double";
        case JTYPE_FLOAT:   return "float";
        case JTYPE_LONG:    return "long";
        case JTYPE_CHAR:    return "char";
        case JTYPE_BOOLEAN: return "int"; /* C has no bool by default */
        case JTYPE_STRING:  return "const char*";
        case JTYPE_INT_ARRAY:    return "int*";
        case JTYPE_DOUBLE_ARRAY: return "double*";
        case JTYPE_STRING_ARRAY: return "const char**";
        default:            return "int";
    }
}

/* Map Java types to Python type comments */
static const char *python_type_str(JavaType jtype) {
    switch (jtype) {
        case JTYPE_INT:     return "int";
        case JTYPE_DOUBLE:  return "float";
        case JTYPE_FLOAT:   return "float";
        case JTYPE_LONG:    return "int";
        case JTYPE_CHAR:    return "str";
        case JTYPE_BOOLEAN: return "bool";
        case JTYPE_STRING:  return "str";
        default:            return "";
    }
}

/* printf format specifier for C based on Java type */
static const char *c_format_spec(JavaType jtype) {
    switch (jtype) {
        case JTYPE_INT:
        case JTYPE_BOOLEAN: return "%d";
        case JTYPE_LONG:    return "%ld";
        case JTYPE_DOUBLE:
        case JTYPE_FLOAT:   return "%f";
        case JTYPE_CHAR:    return "%c";
        case JTYPE_STRING:  return "%s";
        default:            return "%d";
    }
}

static void gen_expr(ASTNode *node);
static void gen_stmt(ASTNode *node);
static void gen_block(ASTNode *node);

/* Attempt to infer the Java type of an expression node */
static JavaType infer_type(ASTNode *node) {
    if (!node) return JTYPE_UNKNOWN;
    switch (node->type) {
        case NODE_INT_LIT:    return JTYPE_INT;
        case NODE_DOUBLE_LIT: return JTYPE_DOUBLE;
        case NODE_STR_LIT:    return JTYPE_STRING;
        case NODE_CHAR_LIT:   return JTYPE_CHAR;
        case NODE_BOOL_LIT:   return JTYPE_BOOLEAN;
        default:
            if (node->java_type != JTYPE_UNKNOWN) return node->java_type;
            return JTYPE_INT;
    }
}

static void gen_expr(ASTNode *node) {
    if (!node) return;
    switch (node->type) {
        case NODE_INT_LIT:
            emit("%d", node->int_val);
            break;
        case NODE_DOUBLE_LIT:
            emit("%g", node->num_val);
            break;
        case NODE_STR_LIT:
            emit("%s", node->name);
            break;
        case NODE_CHAR_LIT:
            emit("'%c'", (char)node->int_val);
            break;
        case NODE_BOOL_LIT:
            if (target == TARGET_PYTHON)
                emit("%s", node->int_val ? "True" : "False");
            else
                emit("%d", node->int_val);
            break;
        case NODE_IDENT:
            emit("%s", node->name);
            break;
        case NODE_BINOP:
            emit("(");
            gen_expr(node->left);
            switch (node->op) {
                case OP_ADD: emit(" + "); break;
                case OP_SUB: emit(" - "); break;
                case OP_MUL: emit(" * "); break;
                case OP_DIV: emit(" / "); break;
                case OP_MOD: emit(" %% "); break;
                case OP_EQ:  emit(" == "); break;
                case OP_NEQ: emit(" != "); break;
                case OP_LT:  emit(" < "); break;
                case OP_GT:  emit(" > "); break;
                case OP_LTE: emit(" <= "); break;
                case OP_GTE: emit(" >= "); break;
                case OP_AND:
                    emit(target == TARGET_PYTHON ? " and " : " && ");
                    break;
                case OP_OR:
                    emit(target == TARGET_PYTHON ? " or " : " || ");
                    break;
                case OP_BITAND: emit(" & "); break;
                case OP_BITOR:  emit(" | "); break;
                case OP_BITXOR: emit(" ^ "); break;
                case OP_SHL:    emit(" << "); break;
                case OP_SHR:    emit(" >> "); break;
                default: emit(" ? "); break;
            }
            gen_expr(node->right);
            emit(")");
            break;
        case NODE_UNARYOP:
            if (node->op == OP_NOT) {
                emit(target == TARGET_PYTHON ? "not " : "!");
                emit("(");
                gen_expr(node->left);
                emit(")");
            } else if (node->op == OP_NEG) {
                emit("-(");
                gen_expr(node->left);
                emit(")");
            } else if (node->op == OP_BITNOT) {
                emit("~(");
                gen_expr(node->left);
                emit(")");
            } else if (node->op == OP_INCREMENT) {
                /* In Python, there's no ++ operator */
                if (target == TARGET_PYTHON) {
                    /* This is tricky in Python - just emit the expression */
                    gen_expr(node->left);
                } else {
                    gen_expr(node->left);
                    emit("++");
                }
            } else if (node->op == OP_DECREMENT) {
                if (target == TARGET_PYTHON) {
                    gen_expr(node->left);
                } else {
                    gen_expr(node->left);
                    emit("--");
                }
            }
            break;
        case NODE_FUNC_CALL:
            emit("%s(", node->name);
            if (node->left) {
                for (int i = 0; i < node->left->item_count; i++) {
                    if (i > 0) emit(", ");
                    gen_expr(node->left->items[i]);
                }
            }
            emit(")");
            break;
        case NODE_METHOD_CALL:
            /* Translate obj.method() - handle it in generated code */
            emit("%s(", node->name);
            if (node->left) {
                for (int i = 0; i < node->left->item_count; i++) {
                    if (i > 0) emit(", ");
                    gen_expr(node->left->items[i]);
                }
            }
            emit(")");
            break;
        case NODE_ARRAY_ACCESS:
            emit("%s[", node->name);
            gen_expr(node->left);
            emit("]");
            break;
        case NODE_NEW_ARRAY:
            if (target == TARGET_PYTHON) {
                emit("[0] * ");
                gen_expr(node->left);
            } else {
                emit("(%s*)calloc(", c_type_str(node->java_type));
                gen_expr(node->left);
                emit(", sizeof(%s))", c_type_str(node->java_type));
            }
            break;
        case NODE_CAST:
            if (target == TARGET_PYTHON) {
                emit("%s(", python_type_str(node->java_type));
                gen_expr(node->left);
                emit(")");
            } else {
                emit("(%s)(", c_type_str(node->java_type));
                gen_expr(node->left);
                emit(")");
            }
            break;
        default:
            emit("/* unknown expr */");
            break;
    }
}

static void gen_stmt(ASTNode *node) {
    if (!node) return;
    switch (node->type) {
        case NODE_PRINT:
            emit_indent();
            if (target == TARGET_PYTHON) {
                emit("print(");
                gen_expr(node->left);
                emit(")\n");
            } else {
                JavaType et = infer_type(node->left);
                emit("printf(\"%s\\n\", ", c_format_spec(et));
                gen_expr(node->left);
                emit(");\n");
            }
            break;
        case NODE_VAR_DECL:
            emit_indent();
            if (target == TARGET_PYTHON) {
                if (node->left) {
                    emit("%s = ", node->name);
                    gen_expr(node->left);
                } else {
                    /* Default initialization */
                    switch (node->java_type) {
                        case JTYPE_INT: case JTYPE_LONG:
                            emit("%s = 0", node->name); break;
                        case JTYPE_DOUBLE: case JTYPE_FLOAT:
                            emit("%s = 0.0", node->name); break;
                        case JTYPE_BOOLEAN:
                            emit("%s = False", node->name); break;
                        case JTYPE_CHAR:
                            emit("%s = ''", node->name); break;
                        case JTYPE_STRING:
                            emit("%s = \"\"", node->name); break;
                        default:
                            emit("%s = None", node->name); break;
                    }
                }
                emit("\n");
            } else {
                emit("%s %s", c_type_str(node->java_type), node->name);
                if (node->left) {
                    emit(" = ");
                    gen_expr(node->left);
                } else {
                    /* C zero-initialization */
                    switch (node->java_type) {
                        case JTYPE_STRING: emit(" = \"\""); break;
                        default: emit(" = 0"); break;
                    }
                }
                emit(";\n");
            }
            break;
        case NODE_ASSIGN:
            emit_indent();
            emit("%s = ", node->name);
            gen_expr(node->left);
            if (target == TARGET_PYTHON)
                emit("\n");
            else
                emit(";\n");
            break;
        case NODE_CLASS_DECL:
            if (target == TARGET_PYTHON) {
                emit_indent();
                emit("class %s:\n", node->name);
                indent_level++;
                gen_block(node->body);
                indent_level--;
                emit("\n");
            } else {
                emit("/* class %s */\n", node->name);
                gen_block(node->body);
            }
            break;
        case NODE_METHOD_DECL:
            if (target == TARGET_PYTHON) {
                emit_indent();
                /* Check if it's the main method */
                if (strcmp(node->name, "main") == 0 && node->is_static) {
                    /* Generate as top-level code or def main */
                    emit("def main():\n");
                    indent_level++;
                    gen_block(node->body);
                    indent_level--;
                    emit("\n");
                    emit_indent();
                    emit("if __name__ == \"__main__\":\n");
                    indent_level++;
                    emit_indent();
                    emit("main()\n");
                    indent_level--;
                } else {
                    emit("def %s(", node->name);
                    if (node->left) {
                        for (int i = 0; i < node->left->item_count; i++) {
                            if (i > 0) emit(", ");
                            emit("%s", node->left->items[i]->name);
                        }
                    }
                    emit("):\n");
                    indent_level++;
                    gen_block(node->body);
                    indent_level--;
                    emit("\n");
                }
            } else {
                emit_indent();
                emit("%s %s(", c_type_str(node->java_type), node->name);
                if (strcmp(node->name, "main") == 0 && node->is_static) {
                    /* C main signature */
                    emit("int argc, char *argv[]");
                } else if (node->left) {
                    for (int i = 0; i < node->left->item_count; i++) {
                        if (i > 0) emit(", ");
                        emit("%s %s",
                            c_type_str(node->left->items[i]->java_type),
                            node->left->items[i]->name);
                    }
                }
                emit(") {\n");
                indent_level++;
                gen_block(node->body);
                /* Add return 0 for main */
                if (strcmp(node->name, "main") == 0) {
                    emit_indent();
                    emit("return 0;\n");
                }
                indent_level--;
                emit_indent();
                emit("}\n\n");
            }
            break;
        case NODE_IF:
            emit_indent();
            if (target == TARGET_PYTHON) {
                emit("if ");
                gen_expr(node->left);
                emit(":\n");
                indent_level++;
                gen_block(node->body);
                indent_level--;
                if (node->right) {
                    /* Check if else-if */
                    if (node->right->type == NODE_IF) {
                        emit_indent();
                        emit("el");
                        /* Recurse, but the gen_stmt for IF will emit "if ..." */
                        gen_stmt(node->right);
                    } else {
                        emit_indent();
                        emit("else:\n");
                        indent_level++;
                        gen_block(node->right);
                        indent_level--;
                    }
                }
            } else {
                emit("if (");
                gen_expr(node->left);
                emit(") {\n");
                indent_level++;
                gen_block(node->body);
                indent_level--;
                emit_indent();
                emit("}");
                if (node->right) {
                    if (node->right->type == NODE_IF) {
                        emit(" else ");
                        gen_stmt(node->right);
                    } else {
                        emit(" else {\n");
                        indent_level++;
                        gen_block(node->right);
                        indent_level--;
                        emit_indent();
                        emit("}");
                    }
                }
                emit("\n");
            }
            break;
        case NODE_WHILE:
            emit_indent();
            if (target == TARGET_PYTHON) {
                emit("while ");
                gen_expr(node->left);
                emit(":\n");
                indent_level++;
                gen_block(node->body);
                indent_level--;
            } else {
                emit("while (");
                gen_expr(node->left);
                emit(") {\n");
                indent_level++;
                gen_block(node->body);
                indent_level--;
                emit_indent();
                emit("}\n");
            }
            break;
        case NODE_FOR:
            emit_indent();
            if (target == TARGET_PYTHON) {
                /* Convert for-loop to Python: figure out range if possible */
                /* Fallback: use while loop pattern */
                /* Emit init */
                if (node->init) {
                    if (node->init->type == NODE_VAR_DECL) {
                        emit("%s = ", node->init->name);
                        if (node->init->left) gen_expr(node->init->left);
                        else emit("0");
                        emit("\n");
                    } else if (node->init->type == NODE_ASSIGN) {
                        emit("%s = ", node->init->name);
                        gen_expr(node->init->left);
                        emit("\n");
                    }
                }
                emit_indent();
                emit("while ");
                gen_expr(node->left);
                emit(":\n");
                indent_level++;
                gen_block(node->body);
                /* Update */
                if (node->update) {
                    emit_indent();
                    if (node->update->type == NODE_ASSIGN) {
                        emit("%s = ", node->update->name);
                        gen_expr(node->update->left);
                        emit("\n");
                    }
                }
                indent_level--;
            } else {
                emit("for (");
                /* Init */
                if (node->init) {
                    if (node->init->type == NODE_VAR_DECL) {
                        emit("%s %s = ", c_type_str(node->init->java_type), node->init->name);
                        if (node->init->left) gen_expr(node->init->left);
                        else emit("0");
                    } else if (node->init->type == NODE_ASSIGN) {
                        emit("%s = ", node->init->name);
                        gen_expr(node->init->left);
                    }
                }
                emit("; ");
                gen_expr(node->left);
                emit("; ");
                /* Update */
                if (node->update) {
                    if (node->update->type == NODE_ASSIGN) {
                        emit("%s = ", node->update->name);
                        gen_expr(node->update->left);
                    }
                }
                emit(") {\n");
                indent_level++;
                gen_block(node->body);
                indent_level--;
                emit_indent();
                emit("}\n");
            }
            break;
        case NODE_RETURN:
            emit_indent();
            if (node->left) {
                emit("return ");
                gen_expr(node->left);
            } else {
                emit("return");
            }
            if (target == TARGET_PYTHON)
                emit("\n");
            else
                emit(";\n");
            break;
        case NODE_EXPR_STMT:
            emit_indent();
            gen_expr(node->left);
            if (target == TARGET_PYTHON)
                emit("\n");
            else
                emit(";\n");
            break;
        default:
            break;
    }
}

static void gen_block(ASTNode *node) {
    if (!node) return;
    if (node->type == NODE_STMT_LIST || node->type == NODE_PROGRAM) {
        for (int i = 0; i < node->item_count; i++)
            gen_stmt(node->items[i]);
    } else {
        gen_stmt(node);
    }
}

CodeGenResult *codegen_generate(ASTNode *root, TargetLang tgt) {
    res = (CodeGenResult *)calloc(1, sizeof(CodeGenResult));
    res->code_capacity = 8192;
    res->code = (char *)malloc(res->code_capacity);
    res->code[0] = '\0';
    target = tgt;
    indent_level = 0;

    if (target == TARGET_C) {
        emit("#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n\n");
    }

    /* For class-based Java code, we unwrap the class and generate function-level code */
    if (root->type == NODE_STMT_LIST || root->type == NODE_PROGRAM) {
        /* Check if top-level items are class declarations */
        int has_class = 0;
        for (int i = 0; i < root->item_count; i++) {
            if (root->items[i]->type == NODE_CLASS_DECL) {
                has_class = 1;
                break;
            }
        }

        if (has_class) {
            /* For C target, first emit non-main methods, then main */
            for (int i = 0; i < root->item_count; i++) {
                if (root->items[i]->type == NODE_CLASS_DECL) {
                    ASTNode *cls = root->items[i];
                    if (cls->body && cls->body->type == NODE_STMT_LIST) {
                        /* First pass: emit non-main methods and field decls */
                        for (int j = 0; j < cls->body->item_count; j++) {
                            ASTNode *member = cls->body->items[j];
                            if (member->type == NODE_METHOD_DECL &&
                                strcmp(member->name, "main") != 0) {
                                gen_stmt(member);
                            } else if (member->type == NODE_VAR_DECL && member->is_static) {
                                /* Static fields become globals in C, module-level in Python */
                                gen_stmt(member);
                            }
                        }
                        /* Second pass: emit main */
                        for (int j = 0; j < cls->body->item_count; j++) {
                            ASTNode *member = cls->body->items[j];
                            if (member->type == NODE_METHOD_DECL &&
                                strcmp(member->name, "main") == 0) {
                                gen_stmt(member);
                            }
                        }
                    }
                } else {
                    gen_stmt(root->items[i]);
                }
            }
        } else {
            /* Non-class Java statements (loose code) */
            if (target == TARGET_C) {
                /* First emit any method declarations */
                for (int i = 0; i < root->item_count; i++) {
                    if (root->items[i]->type == NODE_METHOD_DECL)
                        gen_stmt(root->items[i]);
                }
                /* Wrap non-method code in main() */
                int has_non_method = 0;
                for (int i = 0; i < root->item_count; i++) {
                    if (root->items[i]->type != NODE_METHOD_DECL) {
                        has_non_method = 1;
                        break;
                    }
                }
                if (has_non_method) {
                    emit("int main() {\n");
                    indent_level = 1;
                    for (int i = 0; i < root->item_count; i++) {
                        if (root->items[i]->type != NODE_METHOD_DECL)
                            gen_stmt(root->items[i]);
                    }
                    emit("    return 0;\n}\n");
                }
            } else {
                gen_block(root);
            }
        }
    }

    return res;
}

void codegen_result_free(CodeGenResult *r) {
    if (!r) return;
    if (r->code) free(r->code);
    free(r);
}
