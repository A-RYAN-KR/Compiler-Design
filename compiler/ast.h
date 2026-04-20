#ifndef AST_H
#define AST_H

typedef enum NodeType {
    NODE_PROGRAM,
    NODE_STMT_LIST,
    NODE_CLASS_DECL,
    NODE_METHOD_DECL,
    NODE_VAR_DECL,
    NODE_ASSIGN,
    NODE_IF,
    NODE_WHILE,
    NODE_FOR,
    NODE_RETURN,
    NODE_EXPR_STMT,
    NODE_PRINT,        /* System.out.println */
    NODE_BINOP,
    NODE_UNARYOP,
    NODE_INT_LIT,
    NODE_DOUBLE_LIT,
    NODE_STR_LIT,
    NODE_BOOL_LIT,
    NODE_CHAR_LIT,
    NODE_IDENT,
    NODE_FUNC_CALL,
    NODE_METHOD_CALL,   /* obj.method() */
    NODE_ARRAY_DECL,
    NODE_ARRAY_ACCESS,
    NODE_NEW_ARRAY,
    NODE_CAST,
    NODE_TYPED_PARAM,   /* typed parameter: int x */
} NodeType;

typedef enum OpType {
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD,
    OP_EQ, OP_NEQ, OP_LT, OP_GT, OP_LTE, OP_GTE,
    OP_AND, OP_OR, OP_NOT, OP_NEG,
    OP_BITAND, OP_BITOR, OP_BITXOR, OP_BITNOT,
    OP_SHL, OP_SHR,
    OP_INCREMENT, OP_DECREMENT,
} OpType;

/* Java type names */
typedef enum JavaType {
    JTYPE_VOID,
    JTYPE_INT,
    JTYPE_DOUBLE,
    JTYPE_FLOAT,
    JTYPE_LONG,
    JTYPE_CHAR,
    JTYPE_BOOLEAN,
    JTYPE_STRING,
    JTYPE_INT_ARRAY,
    JTYPE_DOUBLE_ARRAY,
    JTYPE_STRING_ARRAY,
    JTYPE_UNKNOWN,
} JavaType;

/* Access modifiers */
typedef enum AccessMod {
    ACC_DEFAULT,
    ACC_PUBLIC,
    ACC_PRIVATE,
    ACC_PROTECTED,
} AccessMod;

typedef struct ASTNode {
    NodeType type;
    int line;
    char *name;
    double num_val;
    int int_val;
    OpType op;
    JavaType java_type;
    AccessMod access;
    int is_static;
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *body;
    struct ASTNode *init;     /* for-init or var initializer */
    struct ASTNode *update;   /* for-update */
    struct ASTNode **items;
    int item_count;
    int item_capacity;
} ASTNode;

/* Constructors */
ASTNode *ast_new_program(void);
ASTNode *ast_new_stmt_list(void);
ASTNode *ast_new_int_lit(int value, int line);
ASTNode *ast_new_double_lit(double value, int line);
ASTNode *ast_new_str_lit(char *value, int line);
ASTNode *ast_new_char_lit(char value, int line);
ASTNode *ast_new_bool_lit(int value, int line);
ASTNode *ast_new_ident(char *name, int line);
ASTNode *ast_new_binop(OpType op, ASTNode *left, ASTNode *right, int line);
ASTNode *ast_new_unaryop(OpType op, ASTNode *operand, int line);
ASTNode *ast_new_print(ASTNode *expr, int line);
ASTNode *ast_new_var_decl(char *name, JavaType jtype, ASTNode *init, int line);
ASTNode *ast_new_assign(char *name, ASTNode *value, int line);
ASTNode *ast_new_class_decl(char *name, AccessMod access, ASTNode *body, int line);
ASTNode *ast_new_method_decl(char *name, JavaType ret_type, AccessMod access, int is_static,
                             ASTNode *params, ASTNode *body, int line);
ASTNode *ast_new_func_call(char *name, ASTNode *args, int line);
ASTNode *ast_new_method_call(char *obj, char *method, ASTNode *args, int line);
ASTNode *ast_new_if(ASTNode *cond, ASTNode *then_b, ASTNode *else_b, int line);
ASTNode *ast_new_while(ASTNode *cond, ASTNode *body, int line);
ASTNode *ast_new_for(ASTNode *init, ASTNode *cond, ASTNode *update, ASTNode *body, int line);
ASTNode *ast_new_return(ASTNode *expr, int line);
ASTNode *ast_new_expr_stmt(ASTNode *expr, int line);
ASTNode *ast_new_typed_param(char *name, JavaType jtype, int line);
ASTNode *ast_new_array_access(char *name, ASTNode *index, int line);
ASTNode *ast_new_new_array(JavaType jtype, ASTNode *size, int line);
ASTNode *ast_new_cast(JavaType jtype, ASTNode *expr, int line);

/* Utilities */
void ast_add_item(ASTNode *node, ASTNode *item);
void ast_print(ASTNode *node, int indent);
void ast_print_json(ASTNode *node);
void ast_free(ASTNode *node);

const char *node_type_str(NodeType type);
const char *op_type_str(OpType op);
const char *java_type_str(JavaType jtype);

/* Global AST root */
extern ASTNode *ast_root;

#endif
