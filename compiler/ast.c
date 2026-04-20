#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode *ast_root = NULL;

static ASTNode *ast_alloc(NodeType type, int line) {
    ASTNode *node = (ASTNode *)calloc(1, sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: Out of memory\n");
        exit(1);
    }
    node->type = type;
    node->line = line;
    node->java_type = JTYPE_UNKNOWN;
    node->access = ACC_DEFAULT;
    return node;
}

static ASTNode *ast_new_list_node(NodeType type) {
    ASTNode *node = ast_alloc(type, 0);
    node->item_capacity = 16;
    node->items = (ASTNode **)malloc(sizeof(ASTNode *) * node->item_capacity);
    return node;
}

ASTNode *ast_new_program(void) { return ast_new_list_node(NODE_PROGRAM); }
ASTNode *ast_new_stmt_list(void) { return ast_new_list_node(NODE_STMT_LIST); }

ASTNode *ast_new_int_lit(int value, int line) {
    ASTNode *node = ast_alloc(NODE_INT_LIT, line);
    node->int_val = value;
    node->java_type = JTYPE_INT;
    return node;
}

ASTNode *ast_new_double_lit(double value, int line) {
    ASTNode *node = ast_alloc(NODE_DOUBLE_LIT, line);
    node->num_val = value;
    node->java_type = JTYPE_DOUBLE;
    return node;
}

ASTNode *ast_new_str_lit(char *value, int line) {
    ASTNode *node = ast_alloc(NODE_STR_LIT, line);
    node->name = value;
    node->java_type = JTYPE_STRING;
    return node;
}

ASTNode *ast_new_char_lit(char value, int line) {
    ASTNode *node = ast_alloc(NODE_CHAR_LIT, line);
    node->int_val = (int)value;
    node->java_type = JTYPE_CHAR;
    return node;
}

ASTNode *ast_new_bool_lit(int value, int line) {
    ASTNode *node = ast_alloc(NODE_BOOL_LIT, line);
    node->int_val = value;
    node->java_type = JTYPE_BOOLEAN;
    return node;
}

ASTNode *ast_new_ident(char *name, int line) {
    ASTNode *node = ast_alloc(NODE_IDENT, line);
    node->name = name;
    return node;
}

ASTNode *ast_new_binop(OpType op, ASTNode *left, ASTNode *right, int line) {
    ASTNode *node = ast_alloc(NODE_BINOP, line);
    node->op = op;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode *ast_new_unaryop(OpType op, ASTNode *operand, int line) {
    ASTNode *node = ast_alloc(NODE_UNARYOP, line);
    node->op = op;
    node->left = operand;
    return node;
}

ASTNode *ast_new_print(ASTNode *expr, int line) {
    ASTNode *node = ast_alloc(NODE_PRINT, line);
    node->left = expr;
    return node;
}

ASTNode *ast_new_var_decl(char *name, JavaType jtype, ASTNode *init, int line) {
    ASTNode *node = ast_alloc(NODE_VAR_DECL, line);
    node->name = name;
    node->java_type = jtype;
    node->left = init;
    return node;
}

ASTNode *ast_new_assign(char *name, ASTNode *value, int line) {
    ASTNode *node = ast_alloc(NODE_ASSIGN, line);
    node->name = name;
    node->left = value;
    return node;
}

ASTNode *ast_new_class_decl(char *name, AccessMod access, ASTNode *body, int line) {
    ASTNode *node = ast_alloc(NODE_CLASS_DECL, line);
    node->name = name;
    node->access = access;
    node->body = body;
    return node;
}

ASTNode *ast_new_method_decl(char *name, JavaType ret_type, AccessMod access, int is_static,
                             ASTNode *params, ASTNode *body, int line) {
    ASTNode *node = ast_alloc(NODE_METHOD_DECL, line);
    node->name = name;
    node->java_type = ret_type;
    node->access = access;
    node->is_static = is_static;
    node->left = params;
    node->body = body;
    return node;
}

ASTNode *ast_new_func_call(char *name, ASTNode *args, int line) {
    ASTNode *node = ast_alloc(NODE_FUNC_CALL, line);
    node->name = name;
    node->left = args;
    return node;
}

ASTNode *ast_new_method_call(char *obj, char *method, ASTNode *args, int line) {
    ASTNode *node = ast_alloc(NODE_METHOD_CALL, line);
    /* Store as "obj.method" in name */
    int len = strlen(obj) + 1 + strlen(method) + 1;
    node->name = (char *)malloc(len);
    snprintf(node->name, len, "%s.%s", obj, method);
    node->left = args;
    return node;
}

ASTNode *ast_new_if(ASTNode *cond, ASTNode *then_b, ASTNode *else_b, int line) {
    ASTNode *node = ast_alloc(NODE_IF, line);
    node->left = cond;
    node->body = then_b;
    node->right = else_b;
    return node;
}

ASTNode *ast_new_while(ASTNode *cond, ASTNode *body, int line) {
    ASTNode *node = ast_alloc(NODE_WHILE, line);
    node->left = cond;
    node->body = body;
    return node;
}

ASTNode *ast_new_for(ASTNode *init_node, ASTNode *cond, ASTNode *update, ASTNode *body, int line) {
    ASTNode *node = ast_alloc(NODE_FOR, line);
    node->init = init_node;
    node->left = cond;
    node->update = update;
    node->body = body;
    return node;
}

ASTNode *ast_new_return(ASTNode *expr, int line) {
    ASTNode *node = ast_alloc(NODE_RETURN, line);
    node->left = expr;
    return node;
}

ASTNode *ast_new_expr_stmt(ASTNode *expr, int line) {
    ASTNode *node = ast_alloc(NODE_EXPR_STMT, line);
    node->left = expr;
    return node;
}

ASTNode *ast_new_typed_param(char *name, JavaType jtype, int line) {
    ASTNode *node = ast_alloc(NODE_TYPED_PARAM, line);
    node->name = name;
    node->java_type = jtype;
    return node;
}

ASTNode *ast_new_array_access(char *name, ASTNode *index, int line) {
    ASTNode *node = ast_alloc(NODE_ARRAY_ACCESS, line);
    node->name = name;
    node->left = index;
    return node;
}

ASTNode *ast_new_new_array(JavaType jtype, ASTNode *size, int line) {
    ASTNode *node = ast_alloc(NODE_NEW_ARRAY, line);
    node->java_type = jtype;
    node->left = size;
    return node;
}

ASTNode *ast_new_cast(JavaType jtype, ASTNode *expr, int line) {
    ASTNode *node = ast_alloc(NODE_CAST, line);
    node->java_type = jtype;
    node->left = expr;
    return node;
}

void ast_add_item(ASTNode *node, ASTNode *item) {
    if (node->item_count >= node->item_capacity) {
        node->item_capacity *= 2;
        node->items = (ASTNode **)realloc(node->items, sizeof(ASTNode *) * node->item_capacity);
    }
    node->items[node->item_count++] = item;
}

const char *node_type_str(NodeType type) {
    switch (type) {
        case NODE_PROGRAM:      return "Program";
        case NODE_STMT_LIST:    return "StmtList";
        case NODE_CLASS_DECL:   return "ClassDecl";
        case NODE_METHOD_DECL:  return "MethodDecl";
        case NODE_PRINT:        return "Print";
        case NODE_VAR_DECL:     return "VarDecl";
        case NODE_ASSIGN:       return "Assign";
        case NODE_IF:           return "If";
        case NODE_WHILE:        return "While";
        case NODE_FOR:          return "For";
        case NODE_RETURN:       return "Return";
        case NODE_EXPR_STMT:    return "ExprStmt";
        case NODE_BINOP:        return "BinOp";
        case NODE_UNARYOP:      return "UnaryOp";
        case NODE_INT_LIT:      return "IntLit";
        case NODE_DOUBLE_LIT:   return "DoubleLit";
        case NODE_STR_LIT:      return "String";
        case NODE_CHAR_LIT:     return "CharLit";
        case NODE_BOOL_LIT:     return "Bool";
        case NODE_IDENT:        return "Identifier";
        case NODE_FUNC_CALL:    return "FuncCall";
        case NODE_METHOD_CALL:  return "MethodCall";
        case NODE_ARRAY_DECL:   return "ArrayDecl";
        case NODE_ARRAY_ACCESS: return "ArrayAccess";
        case NODE_NEW_ARRAY:    return "NewArray";
        case NODE_CAST:         return "Cast";
        case NODE_TYPED_PARAM:  return "TypedParam";
        default:                return "Unknown";
    }
}

const char *op_type_str(OpType op) {
    switch (op) {
        case OP_ADD: return "+";  case OP_SUB: return "-";
        case OP_MUL: return "*";  case OP_DIV: return "/";
        case OP_MOD: return "%";  case OP_EQ:  return "==";
        case OP_NEQ: return "!="; case OP_LT:  return "<";
        case OP_GT:  return ">";  case OP_LTE: return "<=";
        case OP_GTE: return ">="; case OP_AND: return "&&";
        case OP_OR:  return "||"; case OP_NOT: return "!";
        case OP_NEG: return "-";
        case OP_BITAND: return "&"; case OP_BITOR: return "|";
        case OP_BITXOR: return "^"; case OP_BITNOT: return "~";
        case OP_SHL: return "<<";   case OP_SHR: return ">>";
        case OP_INCREMENT: return "++"; case OP_DECREMENT: return "--";
        default: return "?";
    }
}

const char *java_type_str(JavaType jtype) {
    switch (jtype) {
        case JTYPE_VOID:         return "void";
        case JTYPE_INT:          return "int";
        case JTYPE_DOUBLE:       return "double";
        case JTYPE_FLOAT:        return "float";
        case JTYPE_LONG:         return "long";
        case JTYPE_CHAR:         return "char";
        case JTYPE_BOOLEAN:      return "boolean";
        case JTYPE_STRING:       return "String";
        case JTYPE_INT_ARRAY:    return "int[]";
        case JTYPE_DOUBLE_ARRAY: return "double[]";
        case JTYPE_STRING_ARRAY: return "String[]";
        default:                 return "unknown";
    }
}

static const char *access_mod_str(AccessMod acc) {
    switch (acc) {
        case ACC_PUBLIC:    return "public";
        case ACC_PRIVATE:   return "private";
        case ACC_PROTECTED: return "protected";
        default:            return "";
    }
}

void ast_print(ASTNode *node, int indent) {
    if (!node) return;
    for (int i = 0; i < indent; i++) printf("  ");

    switch (node->type) {
        case NODE_PROGRAM:
        case NODE_STMT_LIST:
            printf("%s\n", node_type_str(node->type));
            for (int i = 0; i < node->item_count; i++)
                ast_print(node->items[i], indent + 1);
            break;
        case NODE_CLASS_DECL:
            printf("ClassDecl: %s %s\n", access_mod_str(node->access), node->name);
            ast_print(node->body, indent + 1);
            break;
        case NODE_METHOD_DECL:
            printf("MethodDecl: %s %s%s %s(",
                access_mod_str(node->access),
                node->is_static ? "static " : "",
                java_type_str(node->java_type), node->name);
            if (node->left) {
                for (int i = 0; i < node->left->item_count; i++) {
                    if (i > 0) printf(", ");
                    printf("%s %s",
                        java_type_str(node->left->items[i]->java_type),
                        node->left->items[i]->name);
                }
            }
            printf(")\n");
            ast_print(node->body, indent + 1);
            break;
        case NODE_PRINT:
            printf("Print\n");
            ast_print(node->left, indent + 1);
            break;
        case NODE_VAR_DECL:
            printf("VarDecl: %s %s\n", java_type_str(node->java_type), node->name);
            if (node->left) ast_print(node->left, indent + 1);
            break;
        case NODE_ASSIGN:
            printf("Assign: %s\n", node->name);
            ast_print(node->left, indent + 1);
            break;
        case NODE_IF:
            printf("If\n");
            ast_print(node->left, indent + 1);
            ast_print(node->body, indent + 1);
            if (node->right) ast_print(node->right, indent + 1);
            break;
        case NODE_WHILE:
            printf("While\n");
            ast_print(node->left, indent + 1);
            ast_print(node->body, indent + 1);
            break;
        case NODE_FOR:
            printf("For\n");
            if (node->init) ast_print(node->init, indent + 1);
            ast_print(node->left, indent + 1);
            if (node->update) ast_print(node->update, indent + 1);
            ast_print(node->body, indent + 1);
            break;
        case NODE_RETURN:
            printf("Return\n");
            ast_print(node->left, indent + 1);
            break;
        case NODE_EXPR_STMT:
            printf("ExprStmt\n");
            ast_print(node->left, indent + 1);
            break;
        case NODE_BINOP:
            printf("BinOp: %s\n", op_type_str(node->op));
            ast_print(node->left, indent + 1);
            ast_print(node->right, indent + 1);
            break;
        case NODE_UNARYOP:
            printf("UnaryOp: %s\n", op_type_str(node->op));
            ast_print(node->left, indent + 1);
            break;
        case NODE_INT_LIT:
            printf("IntLit: %d\n", node->int_val);
            break;
        case NODE_DOUBLE_LIT:
            printf("DoubleLit: %g\n", node->num_val);
            break;
        case NODE_STR_LIT:
            printf("String: %s\n", node->name);
            break;
        case NODE_CHAR_LIT:
            printf("CharLit: '%c'\n", (char)node->int_val);
            break;
        case NODE_BOOL_LIT:
            printf("Bool: %s\n", node->int_val ? "true" : "false");
            break;
        case NODE_IDENT:
            printf("Ident: %s\n", node->name);
            break;
        case NODE_FUNC_CALL:
            printf("FuncCall: %s\n", node->name);
            if (node->left) {
                for (int i = 0; i < node->left->item_count; i++)
                    ast_print(node->left->items[i], indent + 1);
            }
            break;
        case NODE_METHOD_CALL:
            printf("MethodCall: %s\n", node->name);
            if (node->left) {
                for (int i = 0; i < node->left->item_count; i++)
                    ast_print(node->left->items[i], indent + 1);
            }
            break;
        case NODE_ARRAY_ACCESS:
            printf("ArrayAccess: %s\n", node->name);
            ast_print(node->left, indent + 1);
            break;
        case NODE_NEW_ARRAY:
            printf("NewArray: %s\n", java_type_str(node->java_type));
            ast_print(node->left, indent + 1);
            break;
        case NODE_CAST:
            printf("Cast: (%s)\n", java_type_str(node->java_type));
            ast_print(node->left, indent + 1);
            break;
        case NODE_TYPED_PARAM:
            printf("Param: %s %s\n", java_type_str(node->java_type), node->name);
            break;
        default:
            printf("Unknown\n");
            break;
    }
}

static void json_escaped(const char *s) {
    printf("\"");
    while (*s) {
        switch (*s) {
            case '"':  printf("\\\""); break;
            case '\\': printf("\\\\"); break;
            case '\n': printf("\\n");  break;
            case '\t': printf("\\t");  break;
            default:   putchar(*s);
        }
        s++;
    }
    printf("\"");
}

void ast_print_json(ASTNode *node) {
    if (!node) { printf("null"); return; }
    printf("{\"type\":\"%s\",\"line\":%d", node_type_str(node->type), node->line);

    switch (node->type) {
        case NODE_INT_LIT:    printf(",\"value\":%d", node->int_val); break;
        case NODE_DOUBLE_LIT: printf(",\"value\":%g", node->num_val); break;
        case NODE_STR_LIT:    printf(",\"value\":"); json_escaped(node->name); break;
        case NODE_CHAR_LIT:   printf(",\"value\":\"%c\"", (char)node->int_val); break;
        case NODE_BOOL_LIT:   printf(",\"value\":%s", node->int_val ? "true" : "false"); break;
        case NODE_IDENT:
        case NODE_VAR_DECL:
        case NODE_ASSIGN:
        case NODE_CLASS_DECL:
        case NODE_METHOD_DECL:
        case NODE_FUNC_CALL:
        case NODE_METHOD_CALL:
        case NODE_ARRAY_ACCESS:
        case NODE_TYPED_PARAM:
            printf(",\"name\":\"%s\"", node->name); break;
        case NODE_BINOP:
        case NODE_UNARYOP:
            printf(",\"op\":\"%s\"", op_type_str(node->op)); break;
        default: break;
    }

    /* Java type info */
    if (node->java_type != JTYPE_UNKNOWN) {
        printf(",\"javaType\":\"%s\"", java_type_str(node->java_type));
    }

    if (node->left)   { printf(",\"left\":");   ast_print_json(node->left); }
    if (node->right)  { printf(",\"right\":");  ast_print_json(node->right); }
    if (node->body)   { printf(",\"body\":");   ast_print_json(node->body); }
    if (node->init)   { printf(",\"init\":");   ast_print_json(node->init); }
    if (node->update) { printf(",\"update\":"); ast_print_json(node->update); }
    if (node->items && node->item_count > 0) {
        printf(",\"items\":[");
        for (int i = 0; i < node->item_count; i++) {
            if (i > 0) printf(",");
            ast_print_json(node->items[i]);
        }
        printf("]");
    }
    printf("}");
}

void ast_free(ASTNode *node) {
    if (!node) return;
    if (node->name) free(node->name);
    ast_free(node->left);
    ast_free(node->right);
    ast_free(node->body);
    ast_free(node->init);
    ast_free(node->update);
    if (node->items) {
        for (int i = 0; i < node->item_count; i++)
            ast_free(node->items[i]);
        free(node->items);
    }
    free(node);
}
