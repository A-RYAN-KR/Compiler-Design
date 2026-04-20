/**
 * JavaScript-based Java Transpiler (Fallback)
 *
 * Parses a subset of Java and transpiles to Python or C:
 *   - Lexer (tokenization)
 *   - Parser (AST construction)
 *   - Semantic analysis (symbol table + checks)
 *   - Code generation (Python / C)
 */

// ═══════════════════════════════════════════
// LEXER
// ═══════════════════════════════════════════

const TOKEN_TYPES = {
    // Literals
    INT_LITERAL: 'INT_LITERAL', DOUBLE_LITERAL: 'DOUBLE_LITERAL',
    STRING_LIT: 'STRING_LIT', CHAR_LIT: 'CHAR_LIT', BOOL_LIT: 'BOOL_LIT',
    NULL_LIT: 'NULL_LIT',
    IDENTIFIER: 'IDENTIFIER',
    // Keywords
    CLASS: 'CLASS', PUBLIC: 'PUBLIC', PRIVATE: 'PRIVATE', PROTECTED: 'PROTECTED',
    STATIC: 'STATIC', VOID: 'VOID',
    INT: 'INT', DOUBLE: 'DOUBLE', FLOAT: 'FLOAT', LONG: 'LONG',
    CHAR: 'CHAR', BOOLEAN: 'BOOLEAN', STRING_TYPE: 'STRING_TYPE',
    IF: 'IF', ELSE: 'ELSE', WHILE: 'WHILE', FOR: 'FOR',
    RETURN: 'RETURN', NEW: 'NEW',
    SYSOUT_PRINTLN: 'SYSOUT_PRINTLN', SYSOUT_PRINT: 'SYSOUT_PRINT',
    // Operators
    PLUS: 'PLUS', MINUS: 'MINUS', TIMES: 'TIMES',
    DIVIDE: 'DIVIDE', MODULO: 'MODULO',
    EQ: 'EQ', NEQ: 'NEQ', LT: 'LT', GT: 'GT', LTE: 'LTE', GTE: 'GTE',
    AND: 'AND', OR: 'OR', NOT: 'NOT',
    BITAND: 'BITAND', BITOR: 'BITOR', BITXOR: 'BITXOR', BITNOT: 'BITNOT',
    SHL: 'SHL', SHR: 'SHR',
    INCREMENT: 'INCREMENT', DECREMENT: 'DECREMENT',
    PLUS_ASSIGN: 'PLUS_ASSIGN', MINUS_ASSIGN: 'MINUS_ASSIGN',
    TIMES_ASSIGN: 'TIMES_ASSIGN', DIVIDE_ASSIGN: 'DIVIDE_ASSIGN',
    ASSIGN: 'ASSIGN',
    // Delimiters
    LPAREN: 'LPAREN', RPAREN: 'RPAREN',
    LBRACE: 'LBRACE', RBRACE: 'RBRACE',
    LBRACKET: 'LBRACKET', RBRACKET: 'RBRACKET',
    COMMA: 'COMMA', SEMICOLON: 'SEMICOLON', DOT: 'DOT',
    EOF: 'EOF',
};

const KEYWORDS = {
    'class': TOKEN_TYPES.CLASS, 'public': TOKEN_TYPES.PUBLIC,
    'private': TOKEN_TYPES.PRIVATE, 'protected': TOKEN_TYPES.PROTECTED,
    'static': TOKEN_TYPES.STATIC, 'void': TOKEN_TYPES.VOID,
    'int': TOKEN_TYPES.INT, 'double': TOKEN_TYPES.DOUBLE,
    'float': TOKEN_TYPES.FLOAT, 'long': TOKEN_TYPES.LONG,
    'char': TOKEN_TYPES.CHAR, 'boolean': TOKEN_TYPES.BOOLEAN,
    'String': TOKEN_TYPES.STRING_TYPE,
    'if': TOKEN_TYPES.IF, 'else': TOKEN_TYPES.ELSE,
    'while': TOKEN_TYPES.WHILE, 'for': TOKEN_TYPES.FOR,
    'return': TOKEN_TYPES.RETURN, 'new': TOKEN_TYPES.NEW,
    'true': TOKEN_TYPES.BOOL_LIT, 'false': TOKEN_TYPES.BOOL_LIT,
    'null': TOKEN_TYPES.NULL_LIT,
};

function tokenize(source) {
    const tokens = [];
    let pos = 0, line = 1;

    while (pos < source.length) {
        let ch = source[pos];

        // Newline
        if (ch === '\n') { line++; pos++; continue; }
        // Whitespace
        if (/\s/.test(ch)) { pos++; continue; }
        // Line comment
        if (ch === '/' && source[pos + 1] === '/') {
            while (pos < source.length && source[pos] !== '\n') pos++;
            continue;
        }
        // Block comment
        if (ch === '/' && source[pos + 1] === '*') {
            pos += 2;
            while (pos < source.length - 1) {
                if (source[pos] === '\n') line++;
                if (source[pos] === '*' && source[pos + 1] === '/') { pos += 2; break; }
                pos++;
            }
            continue;
        }

        // Check for System.out.println / System.out.print
        if (source.slice(pos, pos + 18) === 'System.out.println') {
            tokens.push({ type: TOKEN_TYPES.SYSOUT_PRINTLN, value: 'System.out.println', line });
            pos += 18; continue;
        }
        if (source.slice(pos, pos + 16) === 'System.out.print' && source[pos + 16] !== 'l') {
            tokens.push({ type: TOKEN_TYPES.SYSOUT_PRINT, value: 'System.out.print', line });
            pos += 16; continue;
        }

        // Multi-char operators (3-char first)
        const three = source.slice(pos, pos + 3);
        // Then 2-char
        const two = source.slice(pos, pos + 2);
        if (two === '++') { tokens.push({ type: TOKEN_TYPES.INCREMENT, value: '++', line }); pos += 2; continue; }
        if (two === '--') { tokens.push({ type: TOKEN_TYPES.DECREMENT, value: '--', line }); pos += 2; continue; }
        if (two === '==') { tokens.push({ type: TOKEN_TYPES.EQ, value: '==', line }); pos += 2; continue; }
        if (two === '!=') { tokens.push({ type: TOKEN_TYPES.NEQ, value: '!=', line }); pos += 2; continue; }
        if (two === '<=') { tokens.push({ type: TOKEN_TYPES.LTE, value: '<=', line }); pos += 2; continue; }
        if (two === '>=') { tokens.push({ type: TOKEN_TYPES.GTE, value: '>=', line }); pos += 2; continue; }
        if (two === '&&') { tokens.push({ type: TOKEN_TYPES.AND, value: '&&', line }); pos += 2; continue; }
        if (two === '||') { tokens.push({ type: TOKEN_TYPES.OR, value: '||', line }); pos += 2; continue; }
        if (two === '<<') { tokens.push({ type: TOKEN_TYPES.SHL, value: '<<', line }); pos += 2; continue; }
        if (two === '>>') { tokens.push({ type: TOKEN_TYPES.SHR, value: '>>', line }); pos += 2; continue; }
        if (two === '+=') { tokens.push({ type: TOKEN_TYPES.PLUS_ASSIGN, value: '+=', line }); pos += 2; continue; }
        if (two === '-=') { tokens.push({ type: TOKEN_TYPES.MINUS_ASSIGN, value: '-=', line }); pos += 2; continue; }
        if (two === '*=') { tokens.push({ type: TOKEN_TYPES.TIMES_ASSIGN, value: '*=', line }); pos += 2; continue; }
        if (two === '/=') { tokens.push({ type: TOKEN_TYPES.DIVIDE_ASSIGN, value: '/=', line }); pos += 2; continue; }

        // Single-char operators / delimiters
        const singles = {
            '+': TOKEN_TYPES.PLUS, '-': TOKEN_TYPES.MINUS,
            '*': TOKEN_TYPES.TIMES, '/': TOKEN_TYPES.DIVIDE,
            '%': TOKEN_TYPES.MODULO, '<': TOKEN_TYPES.LT,
            '>': TOKEN_TYPES.GT, '!': TOKEN_TYPES.NOT,
            '&': TOKEN_TYPES.BITAND, '|': TOKEN_TYPES.BITOR,
            '^': TOKEN_TYPES.BITXOR, '~': TOKEN_TYPES.BITNOT,
            '=': TOKEN_TYPES.ASSIGN, '(': TOKEN_TYPES.LPAREN,
            ')': TOKEN_TYPES.RPAREN, '{': TOKEN_TYPES.LBRACE,
            '}': TOKEN_TYPES.RBRACE, '[': TOKEN_TYPES.LBRACKET,
            ']': TOKEN_TYPES.RBRACKET, ',': TOKEN_TYPES.COMMA,
            ';': TOKEN_TYPES.SEMICOLON, '.': TOKEN_TYPES.DOT,
        };
        if (singles[ch]) {
            tokens.push({ type: singles[ch], value: ch, line });
            pos++;
            continue;
        }

        // Number
        if (/[0-9]/.test(ch)) {
            let num = '';
            let isDouble = false;
            while (pos < source.length && /[0-9.]/.test(source[pos])) {
                if (source[pos] === '.') isDouble = true;
                num += source[pos++];
            }
            // Skip suffix like f, d, L
            if (pos < source.length && /[fFdDlL]/.test(source[pos])) pos++;
            if (isDouble) {
                tokens.push({ type: TOKEN_TYPES.DOUBLE_LITERAL, value: parseFloat(num), line });
            } else {
                tokens.push({ type: TOKEN_TYPES.INT_LITERAL, value: parseInt(num, 10), line });
            }
            continue;
        }

        // String literal
        if (ch === '"') {
            let str = '"';
            pos++;
            while (pos < source.length && source[pos] !== '"') {
                if (source[pos] === '\\') { str += source[pos++]; }
                str += source[pos++];
            }
            str += '"';
            pos++; // closing quote
            tokens.push({ type: TOKEN_TYPES.STRING_LIT, value: str, line });
            continue;
        }

        // Char literal
        if (ch === "'") {
            pos++; // opening quote
            let charVal = source[pos];
            if (charVal === '\\') { pos++; charVal = source[pos]; }
            pos++; // char
            pos++; // closing quote
            tokens.push({ type: TOKEN_TYPES.CHAR_LIT, value: charVal, line });
            continue;
        }

        // Identifier / keyword
        if (/[a-zA-Z_]/.test(ch)) {
            let id = '';
            while (pos < source.length && /[a-zA-Z0-9_]/.test(source[pos])) id += source[pos++];
            if (KEYWORDS[id]) {
                if (id === 'true' || id === 'false') {
                    tokens.push({ type: TOKEN_TYPES.BOOL_LIT, value: id === 'true', line });
                } else if (id === 'null') {
                    tokens.push({ type: TOKEN_TYPES.NULL_LIT, value: 'null', line });
                } else {
                    tokens.push({ type: KEYWORDS[id], value: id, line });
                }
            } else {
                tokens.push({ type: TOKEN_TYPES.IDENTIFIER, value: id, line });
            }
            continue;
        }

        throw new Error(`Lexical Error: Unknown character '${ch}' at line ${line}`);
    }

    tokens.push({ type: TOKEN_TYPES.EOF, value: null, line });
    return tokens;
}

// ═══════════════════════════════════════════
// PARSER (Recursive Descent + Pratt)
// ═══════════════════════════════════════════

const TYPE_TOKENS = new Set([
    TOKEN_TYPES.INT, TOKEN_TYPES.DOUBLE, TOKEN_TYPES.FLOAT,
    TOKEN_TYPES.LONG, TOKEN_TYPES.CHAR, TOKEN_TYPES.BOOLEAN,
    TOKEN_TYPES.STRING_TYPE, TOKEN_TYPES.VOID,
]);

const TYPE_MAP = {
    [TOKEN_TYPES.INT]: 'int', [TOKEN_TYPES.DOUBLE]: 'double',
    [TOKEN_TYPES.FLOAT]: 'float', [TOKEN_TYPES.LONG]: 'long',
    [TOKEN_TYPES.CHAR]: 'char', [TOKEN_TYPES.BOOLEAN]: 'boolean',
    [TOKEN_TYPES.STRING_TYPE]: 'String', [TOKEN_TYPES.VOID]: 'void',
};

const ACCESS_TOKENS = new Set([TOKEN_TYPES.PUBLIC, TOKEN_TYPES.PRIVATE, TOKEN_TYPES.PROTECTED]);

class Parser {
    constructor(tokens) {
        this.tokens = tokens;
        this.pos = 0;
    }

    peek() { return this.tokens[this.pos]; }
    advance() { return this.tokens[this.pos++]; }

    expect(type) {
        const tok = this.advance();
        if (tok.type !== type) {
            throw new Error(`Syntax Error (line ${tok.line}): Expected ${type}, got ${tok.type} '${tok.value}'`);
        }
        return tok;
    }

    parse() {
        const stmts = [];
        while (this.peek().type !== TOKEN_TYPES.EOF) {
            stmts.push(this.parseTopLevel());
        }
        return { type: 'Program', items: stmts, line: 0 };
    }

    isAccessMod() { return ACCESS_TOKENS.has(this.peek().type); }
    isTypeToken() { return TYPE_TOKENS.has(this.peek().type); }

    parseAccessMod() {
        if (this.isAccessMod()) return this.advance().value;
        return 'default';
    }

    parseStatic() {
        if (this.peek().type === TOKEN_TYPES.STATIC) { this.advance(); return true; }
        return false;
    }

    parseType() {
        const tok = this.advance();
        let typeName = TYPE_MAP[tok.type];
        if (!typeName) throw new Error(`Syntax Error (line ${tok.line}): Expected type, got '${tok.value}'`);
        // Check for array type
        if (this.peek().type === TOKEN_TYPES.LBRACKET) {
            this.advance(); // [
            this.expect(TOKEN_TYPES.RBRACKET); // ]
            typeName += '[]';
        }
        return typeName;
    }

    parseTopLevel() {
        // Could be class declaration or loose statements
        const savedPos = this.pos;
        const access = this.parseAccessMod();

        if (this.peek().type === TOKEN_TYPES.CLASS) {
            return this.parseClassDecl(access);
        }

        // Rewind if no class found
        this.pos = savedPos;
        return this.parseStatement();
    }

    parseClassDecl(access) {
        this.expect(TOKEN_TYPES.CLASS);
        const name = this.expect(TOKEN_TYPES.IDENTIFIER).value;
        this.expect(TOKEN_TYPES.LBRACE);
        const members = [];
        while (this.peek().type !== TOKEN_TYPES.RBRACE) {
            members.push(this.parseClassMember());
        }
        this.expect(TOKEN_TYPES.RBRACE);
        return {
            type: 'ClassDecl', name, access,
            body: { type: 'StmtList', items: members },
            line: this.peek().line,
        };
    }

    parseClassMember() {
        const access = this.parseAccessMod();
        const isStatic = this.parseStatic();

        // Must be a type followed by identifier
        const typeName = this.parseType();
        const name = this.expect(TOKEN_TYPES.IDENTIFIER).value;

        if (this.peek().type === TOKEN_TYPES.LPAREN) {
            // Method
            return this.parseMethodDecl(name, typeName, access, isStatic);
        } else {
            // Field
            return this.parseFieldDecl(name, typeName, access, isStatic);
        }
    }

    parseMethodDecl(name, returnType, access, isStatic) {
        this.expect(TOKEN_TYPES.LPAREN);
        const params = [];
        if (this.peek().type !== TOKEN_TYPES.RPAREN) {
            params.push(this.parseTypedParam());
            while (this.peek().type === TOKEN_TYPES.COMMA) {
                this.advance();
                params.push(this.parseTypedParam());
            }
        }
        this.expect(TOKEN_TYPES.RPAREN);
        this.expect(TOKEN_TYPES.LBRACE);
        const body = [];
        while (this.peek().type !== TOKEN_TYPES.RBRACE) {
            body.push(this.parseStatement());
        }
        this.expect(TOKEN_TYPES.RBRACE);
        return {
            type: 'MethodDecl', name, returnType, access, isStatic,
            left: params.length > 0 ? { type: 'StmtList', items: params } : null,
            body: { type: 'StmtList', items: body },
            line: this.peek().line,
        };
    }

    parseFieldDecl(name, typeName, access, isStatic) {
        let init = null;
        if (this.peek().type === TOKEN_TYPES.ASSIGN) {
            this.advance();
            init = this.parseExpression();
        }
        this.expect(TOKEN_TYPES.SEMICOLON);
        return {
            type: 'VarDecl', name, javaType: typeName,
            left: init, access, isStatic,
            line: this.peek().line,
        };
    }

    parseTypedParam() {
        const typeName = this.parseType();
        const name = this.expect(TOKEN_TYPES.IDENTIFIER).value;
        return { type: 'TypedParam', name, javaType: typeName, line: this.peek().line };
    }

    parseStatement() {
        const tok = this.peek();

        if (tok.type === TOKEN_TYPES.IF) return this.parseIf();
        if (tok.type === TOKEN_TYPES.WHILE) return this.parseWhile();
        if (tok.type === TOKEN_TYPES.FOR) return this.parseFor();
        if (tok.type === TOKEN_TYPES.RETURN) return this.parseReturn();
        if (tok.type === TOKEN_TYPES.SYSOUT_PRINTLN || tok.type === TOKEN_TYPES.SYSOUT_PRINT) return this.parsePrint();

        // Type-prefixed: var decl
        if (this.isTypeToken()) {
            return this.parseVarDeclStmt();
        }

        // Identifier: could be assignment or expr
        if (tok.type === TOKEN_TYPES.IDENTIFIER) {
            // Look ahead for = , += etc.
            const next = this.tokens[this.pos + 1];
            if (next && (next.type === TOKEN_TYPES.ASSIGN ||
                         next.type === TOKEN_TYPES.PLUS_ASSIGN ||
                         next.type === TOKEN_TYPES.MINUS_ASSIGN ||
                         next.type === TOKEN_TYPES.TIMES_ASSIGN ||
                         next.type === TOKEN_TYPES.DIVIDE_ASSIGN)) {
                return this.parseAssignStmt();
            }
            // Array assignment: id[expr] = expr;
            if (next && next.type === TOKEN_TYPES.LBRACKET) {
                const next3 = this.tokens[this.pos + 2]; // look further for assign after bracket
                // This is complex, just try expr stmt
            }
        }

        return this.parseExprStmt();
    }

    parseVarDeclStmt() {
        const typeName = this.parseType();
        const name = this.expect(TOKEN_TYPES.IDENTIFIER).value;
        let init = null;
        if (this.peek().type === TOKEN_TYPES.ASSIGN) {
            this.advance();
            init = this.parseExpression();
        }
        this.expect(TOKEN_TYPES.SEMICOLON);
        return { type: 'VarDecl', name, javaType: typeName, left: init, line: this.peek().line };
    }

    parseAssignStmt() {
        const nameTok = this.advance();
        const opTok = this.advance();
        const value = this.parseExpression();
        this.expect(TOKEN_TYPES.SEMICOLON);

        let rhs = value;
        if (opTok.type === TOKEN_TYPES.PLUS_ASSIGN) {
            rhs = { type: 'BinOp', op: '+', left: { type: 'Identifier', name: nameTok.value, line: nameTok.line }, right: value, line: nameTok.line };
        } else if (opTok.type === TOKEN_TYPES.MINUS_ASSIGN) {
            rhs = { type: 'BinOp', op: '-', left: { type: 'Identifier', name: nameTok.value, line: nameTok.line }, right: value, line: nameTok.line };
        } else if (opTok.type === TOKEN_TYPES.TIMES_ASSIGN) {
            rhs = { type: 'BinOp', op: '*', left: { type: 'Identifier', name: nameTok.value, line: nameTok.line }, right: value, line: nameTok.line };
        } else if (opTok.type === TOKEN_TYPES.DIVIDE_ASSIGN) {
            rhs = { type: 'BinOp', op: '/', left: { type: 'Identifier', name: nameTok.value, line: nameTok.line }, right: value, line: nameTok.line };
        }

        return { type: 'Assign', name: nameTok.value, left: rhs, line: nameTok.line };
    }

    parsePrint() {
        const tok = this.advance(); // SYSOUT_PRINTLN or SYSOUT_PRINT
        this.expect(TOKEN_TYPES.LPAREN);
        let expr = null;
        if (this.peek().type !== TOKEN_TYPES.RPAREN) {
            expr = this.parseExpression();
        } else {
            expr = { type: 'String', value: '""', line: tok.line };
        }
        this.expect(TOKEN_TYPES.RPAREN);
        this.expect(TOKEN_TYPES.SEMICOLON);
        return { type: 'Print', left: expr, line: tok.line };
    }

    parseIf() {
        const tok = this.advance(); // IF
        this.expect(TOKEN_TYPES.LPAREN);
        const cond = this.parseExpression();
        this.expect(TOKEN_TYPES.RPAREN);
        const thenBlock = this.parseBlock();

        let elseBlock = null;
        if (this.peek().type === TOKEN_TYPES.ELSE) {
            this.advance();
            if (this.peek().type === TOKEN_TYPES.IF) {
                elseBlock = this.parseIf(); // else if
            } else {
                elseBlock = this.parseBlock();
            }
        }

        return {
            type: 'If', left: cond,
            body: thenBlock, right: elseBlock,
            line: tok.line,
        };
    }

    parseBlock() {
        this.expect(TOKEN_TYPES.LBRACE);
        const stmts = [];
        while (this.peek().type !== TOKEN_TYPES.RBRACE) {
            stmts.push(this.parseStatement());
        }
        this.expect(TOKEN_TYPES.RBRACE);
        return { type: 'StmtList', items: stmts };
    }

    parseWhile() {
        const tok = this.advance(); // WHILE
        this.expect(TOKEN_TYPES.LPAREN);
        const cond = this.parseExpression();
        this.expect(TOKEN_TYPES.RPAREN);
        const body = this.parseBlock();
        return { type: 'While', left: cond, body, line: tok.line };
    }

    parseFor() {
        const tok = this.advance(); // FOR
        this.expect(TOKEN_TYPES.LPAREN);

        // Init
        let init = null;
        if (this.isTypeToken()) {
            const typeName = this.parseType();
            const name = this.expect(TOKEN_TYPES.IDENTIFIER).value;
            this.expect(TOKEN_TYPES.ASSIGN);
            const initExpr = this.parseExpression();
            init = { type: 'VarDecl', name, javaType: typeName, left: initExpr, line: tok.line };
        } else if (this.peek().type === TOKEN_TYPES.IDENTIFIER) {
            const name = this.advance();
            this.expect(TOKEN_TYPES.ASSIGN);
            const initExpr = this.parseExpression();
            init = { type: 'Assign', name: name.value, left: initExpr, line: name.line };
        }
        this.expect(TOKEN_TYPES.SEMICOLON);

        // Condition
        const cond = this.parseExpression();
        this.expect(TOKEN_TYPES.SEMICOLON);

        // Update
        let update = null;
        if (this.peek().type === TOKEN_TYPES.IDENTIFIER) {
            const uName = this.advance();
            if (this.peek().type === TOKEN_TYPES.INCREMENT) {
                this.advance();
                update = {
                    type: 'Assign', name: uName.value,
                    left: { type: 'BinOp', op: '+', left: { type: 'Identifier', name: uName.value, line: uName.line }, right: { type: 'IntLit', value: 1, line: uName.line }, line: uName.line },
                    line: uName.line,
                };
            } else if (this.peek().type === TOKEN_TYPES.DECREMENT) {
                this.advance();
                update = {
                    type: 'Assign', name: uName.value,
                    left: { type: 'BinOp', op: '-', left: { type: 'Identifier', name: uName.value, line: uName.line }, right: { type: 'IntLit', value: 1, line: uName.line }, line: uName.line },
                    line: uName.line,
                };
            } else if (this.peek().type === TOKEN_TYPES.PLUS_ASSIGN) {
                this.advance();
                const val = this.parseExpression();
                update = {
                    type: 'Assign', name: uName.value,
                    left: { type: 'BinOp', op: '+', left: { type: 'Identifier', name: uName.value, line: uName.line }, right: val, line: uName.line },
                    line: uName.line,
                };
            } else if (this.peek().type === TOKEN_TYPES.ASSIGN) {
                this.advance();
                const val = this.parseExpression();
                update = { type: 'Assign', name: uName.value, left: val, line: uName.line };
            }
        } else if (this.peek().type === TOKEN_TYPES.INCREMENT) {
            // ++i form — but for simplicity we'll skip
        }
        this.expect(TOKEN_TYPES.RPAREN);
        const body = this.parseBlock();

        return { type: 'For', init, left: cond, update, body, line: tok.line };
    }

    parseReturn() {
        const tok = this.advance(); // RETURN
        let expr = null;
        if (this.peek().type !== TOKEN_TYPES.SEMICOLON) {
            expr = this.parseExpression();
        }
        this.expect(TOKEN_TYPES.SEMICOLON);
        return { type: 'Return', left: expr, line: tok.line };
    }

    parseExprStmt() {
        const expr = this.parseExpression();
        this.expect(TOKEN_TYPES.SEMICOLON);
        return { type: 'ExprStmt', left: expr, line: expr.line };
    }

    // Pratt parser for expressions
    parseExpression(minPrec = 0) {
        let left = this.parseUnary();

        const precMap = {
            [TOKEN_TYPES.OR]: 1, [TOKEN_TYPES.AND]: 2,
            [TOKEN_TYPES.BITOR]: 3, [TOKEN_TYPES.BITXOR]: 4, [TOKEN_TYPES.BITAND]: 5,
            [TOKEN_TYPES.EQ]: 6, [TOKEN_TYPES.NEQ]: 6,
            [TOKEN_TYPES.LT]: 7, [TOKEN_TYPES.GT]: 7,
            [TOKEN_TYPES.LTE]: 7, [TOKEN_TYPES.GTE]: 7,
            [TOKEN_TYPES.SHL]: 8, [TOKEN_TYPES.SHR]: 8,
            [TOKEN_TYPES.PLUS]: 9, [TOKEN_TYPES.MINUS]: 9,
            [TOKEN_TYPES.TIMES]: 10, [TOKEN_TYPES.DIVIDE]: 10,
            [TOKEN_TYPES.MODULO]: 10,
        };

        const opMap = {
            [TOKEN_TYPES.PLUS]: '+', [TOKEN_TYPES.MINUS]: '-',
            [TOKEN_TYPES.TIMES]: '*', [TOKEN_TYPES.DIVIDE]: '/',
            [TOKEN_TYPES.MODULO]: '%', [TOKEN_TYPES.EQ]: '==',
            [TOKEN_TYPES.NEQ]: '!=', [TOKEN_TYPES.LT]: '<',
            [TOKEN_TYPES.GT]: '>', [TOKEN_TYPES.LTE]: '<=',
            [TOKEN_TYPES.GTE]: '>=', [TOKEN_TYPES.AND]: '&&',
            [TOKEN_TYPES.OR]: '||', [TOKEN_TYPES.BITAND]: '&',
            [TOKEN_TYPES.BITOR]: '|', [TOKEN_TYPES.BITXOR]: '^',
            [TOKEN_TYPES.SHL]: '<<', [TOKEN_TYPES.SHR]: '>>',
        };

        while (precMap[this.peek().type] !== undefined && precMap[this.peek().type] > minPrec) {
            const opTok = this.advance();
            const right = this.parseExpression(precMap[opTok.type]);
            left = { type: 'BinOp', op: opMap[opTok.type], left, right, line: opTok.line };
        }

        // Postfix ++ / --
        while (this.peek().type === TOKEN_TYPES.INCREMENT || this.peek().type === TOKEN_TYPES.DECREMENT) {
            const opTok = this.advance();
            left = { type: 'UnaryOp', op: opTok.value, left, line: opTok.line };
        }

        return left;
    }

    parseUnary() {
        if (this.peek().type === TOKEN_TYPES.NOT) {
            const tok = this.advance(); return { type: 'UnaryOp', op: '!', left: this.parseUnary(), line: tok.line };
        }
        if (this.peek().type === TOKEN_TYPES.BITNOT) {
            const tok = this.advance(); return { type: 'UnaryOp', op: '~', left: this.parseUnary(), line: tok.line };
        }
        if (this.peek().type === TOKEN_TYPES.MINUS) {
            const tok = this.advance(); return { type: 'UnaryOp', op: '-', left: this.parseUnary(), line: tok.line };
        }
        if (this.peek().type === TOKEN_TYPES.INCREMENT) {
            const tok = this.advance(); return { type: 'UnaryOp', op: '++', left: this.parseUnary(), line: tok.line };
        }
        if (this.peek().type === TOKEN_TYPES.DECREMENT) {
            const tok = this.advance(); return { type: 'UnaryOp', op: '--', left: this.parseUnary(), line: tok.line };
        }

        // Cast expression: (type) expr
        if (this.peek().type === TOKEN_TYPES.LPAREN) {
            const nextTok = this.tokens[this.pos + 1];
            if (nextTok && TYPE_TOKENS.has(nextTok.type)) {
                const afterType = this.tokens[this.pos + 2];
                if (afterType && afterType.type === TOKEN_TYPES.RPAREN) {
                    this.advance(); // (
                    const typeName = this.parseType();
                    this.expect(TOKEN_TYPES.RPAREN);
                    const expr = this.parsePrimary();
                    return { type: 'Cast', javaType: typeName, left: expr, line: nextTok.line };
                }
            }
        }

        return this.parsePrimary();
    }

    parsePrimary() {
        const tok = this.peek();

        if (tok.type === TOKEN_TYPES.INT_LITERAL) {
            this.advance();
            return { type: 'IntLit', value: tok.value, line: tok.line };
        }
        if (tok.type === TOKEN_TYPES.DOUBLE_LITERAL) {
            this.advance();
            return { type: 'DoubleLit', value: tok.value, line: tok.line };
        }
        if (tok.type === TOKEN_TYPES.STRING_LIT) {
            this.advance();
            return { type: 'String', value: tok.value, line: tok.line };
        }
        if (tok.type === TOKEN_TYPES.CHAR_LIT) {
            this.advance();
            return { type: 'CharLit', value: tok.value, line: tok.line };
        }
        if (tok.type === TOKEN_TYPES.BOOL_LIT) {
            this.advance();
            return { type: 'Bool', value: tok.value, line: tok.line };
        }
        if (tok.type === TOKEN_TYPES.NULL_LIT) {
            this.advance();
            return { type: 'Identifier', name: 'null', line: tok.line };
        }
        if (tok.type === TOKEN_TYPES.NEW) {
            this.advance(); // new
            const typeName = this.parseType();
            // For now only: new type[size]
            // The type parsing already consumed [], so handle inline
            // Actually let's handle it here
            if (this.peek().type === TOKEN_TYPES.LBRACKET) {
                this.advance();
                const size = this.parseExpression();
                this.expect(TOKEN_TYPES.RBRACKET);
                return { type: 'NewArray', javaType: typeName, left: size, line: tok.line };
            }
            // new Type(args) — constructor call
            if (this.peek().type === TOKEN_TYPES.LPAREN) {
                this.advance();
                const args = [];
                if (this.peek().type !== TOKEN_TYPES.RPAREN) {
                    args.push(this.parseExpression());
                    while (this.peek().type === TOKEN_TYPES.COMMA) {
                        this.advance();
                        args.push(this.parseExpression());
                    }
                }
                this.expect(TOKEN_TYPES.RPAREN);
                return {
                    type: 'FuncCall', name: typeName,
                    left: args.length > 0 ? { type: 'StmtList', items: args } : null,
                    line: tok.line,
                };
            }
            return { type: 'Identifier', name: typeName, line: tok.line };
        }

        if (tok.type === TOKEN_TYPES.IDENTIFIER) {
            this.advance();
            // Method call: obj.method(args)
            if (this.peek().type === TOKEN_TYPES.DOT) {
                this.advance(); // .
                const method = this.expect(TOKEN_TYPES.IDENTIFIER).value;
                if (this.peek().type === TOKEN_TYPES.LPAREN) {
                    this.advance(); // (
                    const args = [];
                    if (this.peek().type !== TOKEN_TYPES.RPAREN) {
                        args.push(this.parseExpression());
                        while (this.peek().type === TOKEN_TYPES.COMMA) {
                            this.advance();
                            args.push(this.parseExpression());
                        }
                    }
                    this.expect(TOKEN_TYPES.RPAREN);
                    return {
                        type: 'MethodCall', name: `${tok.value}.${method}`,
                        left: args.length > 0 ? { type: 'StmtList', items: args } : null,
                        line: tok.line,
                    };
                }
                // Field access
                return { type: 'Identifier', name: `${tok.value}.${method}`, line: tok.line };
            }
            // Function call
            if (this.peek().type === TOKEN_TYPES.LPAREN) {
                this.advance(); // (
                const args = [];
                if (this.peek().type !== TOKEN_TYPES.RPAREN) {
                    args.push(this.parseExpression());
                    while (this.peek().type === TOKEN_TYPES.COMMA) {
                        this.advance();
                        args.push(this.parseExpression());
                    }
                }
                this.expect(TOKEN_TYPES.RPAREN);
                return {
                    type: 'FuncCall', name: tok.value,
                    left: args.length > 0 ? { type: 'StmtList', items: args } : null,
                    line: tok.line,
                };
            }
            // Array access
            if (this.peek().type === TOKEN_TYPES.LBRACKET) {
                this.advance();
                const index = this.parseExpression();
                this.expect(TOKEN_TYPES.RBRACKET);
                return { type: 'ArrayAccess', name: tok.value, left: index, line: tok.line };
            }
            return { type: 'Identifier', name: tok.value, line: tok.line };
        }
        if (tok.type === TOKEN_TYPES.LPAREN) {
            this.advance();
            const expr = this.parseExpression();
            this.expect(TOKEN_TYPES.RPAREN);
            return expr;
        }
        throw new Error(`Syntax Error (line ${tok.line}): Unexpected token '${tok.value}'`);
    }
}

// ═══════════════════════════════════════════
// SEMANTIC ANALYSIS
// ═══════════════════════════════════════════

function semanticAnalyze(ast) {
    const errors = [];
    const symbols = [];
    const scopes = [{}];

    function currentScope() { return scopes[scopes.length - 1]; }
    function pushScope() { scopes.push({}); }
    function popScope() { scopes.pop(); }

    function lookup(name) {
        for (let i = scopes.length - 1; i >= 0; i--) {
            if (scopes[i][name]) return scopes[i][name];
        }
        return null;
    }

    function declare(name, kind, javaType, paramCount, line) {
        const scope = currentScope();
        if (scope[name]) {
            errors.push({ line, message: `'${name}' already declared in this scope (line ${scope[name].line})` });
            return;
        }
        const sym = { name, type: kind, javaType, paramCount, line };
        scope[name] = sym;
        if (scopes.length === 1) symbols.push(sym);
    }

    function analyzeExpr(node) {
        if (!node) return;
        switch (node.type) {
            case 'Identifier': {
                if (node.name !== 'null' && !node.name.includes('.') && !lookup(node.name)) {
                    errors.push({ line: node.line, message: `Undeclared identifier '${node.name}'` });
                }
                break;
            }
            case 'BinOp':
                analyzeExpr(node.left);
                analyzeExpr(node.right);
                break;
            case 'UnaryOp':
                analyzeExpr(node.left);
                break;
            case 'FuncCall': {
                const sym = lookup(node.name);
                if (!sym) {
                    // Don't error on constructors or unknown calls for now
                } else if (sym.type !== 'function') {
                    errors.push({ line: node.line, message: `'${node.name}' is not a method` });
                } else {
                    const argCount = node.left ? node.left.items.length : 0;
                    if (argCount !== sym.paramCount) {
                        errors.push({ line: node.line, message: `Method '${node.name}' expects ${sym.paramCount} arguments, got ${argCount}` });
                    }
                }
                if (node.left) node.left.items.forEach(analyzeExpr);
                break;
            }
            case 'MethodCall':
                if (node.left) node.left.items.forEach(analyzeExpr);
                break;
            case 'ArrayAccess':
                analyzeExpr(node.left);
                break;
            case 'NewArray':
                analyzeExpr(node.left);
                break;
            case 'Cast':
                analyzeExpr(node.left);
                break;
        }
    }

    function analyzeStmt(node) {
        if (!node) return;
        switch (node.type) {
            case 'Program':
            case 'StmtList':
                node.items.forEach(analyzeStmt);
                break;
            case 'ClassDecl':
                declare(node.name, 'class', 'class', 0, node.line);
                pushScope();
                analyzeStmt(node.body);
                popScope();
                break;
            case 'Print':
                analyzeExpr(node.left);
                break;
            case 'VarDecl':
                if (node.left) analyzeExpr(node.left);
                declare(node.name, 'variable', node.javaType || 'unknown', 0, node.line);
                break;
            case 'Assign': {
                const sym = lookup(node.name);
                if (!sym) errors.push({ line: node.line, message: `Undeclared variable '${node.name}'` });
                else if (sym.type === 'function') errors.push({ line: node.line, message: `Cannot assign to method '${node.name}'` });
                analyzeExpr(node.left);
                break;
            }
            case 'MethodDecl': {
                const paramCount = node.left ? node.left.items.length : 0;
                declare(node.name, 'function', node.returnType || 'void', paramCount, node.line);
                pushScope();
                if (node.left) {
                    node.left.items.forEach(p => declare(p.name, 'variable', p.javaType || 'unknown', 0, p.line));
                }
                analyzeStmt(node.body);
                popScope();
                break;
            }
            case 'If':
                analyzeExpr(node.left);
                analyzeStmt(node.body);
                if (node.right) analyzeStmt(node.right);
                break;
            case 'While':
                analyzeExpr(node.left);
                analyzeStmt(node.body);
                break;
            case 'For':
                if (node.init) analyzeStmt(node.init);
                analyzeExpr(node.left);
                if (node.update) analyzeStmt(node.update);
                analyzeStmt(node.body);
                break;
            case 'Return':
                if (node.left) analyzeExpr(node.left);
                break;
            case 'ExprStmt':
                analyzeExpr(node.left);
                break;
        }
    }

    analyzeStmt(ast);
    return { errors, symbols };
}

// ═══════════════════════════════════════════
// CODE GENERATOR
// ═══════════════════════════════════════════

const C_TYPE_MAP = {
    'int': 'int', 'double': 'double', 'float': 'float', 'long': 'long',
    'char': 'char', 'boolean': 'int', 'String': 'const char*', 'void': 'void',
    'int[]': 'int*', 'double[]': 'double*', 'String[]': 'const char**',
};

const PY_TYPE_MAP = {
    'int': 'int', 'double': 'float', 'float': 'float', 'long': 'int',
    'char': 'str', 'boolean': 'bool', 'String': 'str', 'void': '',
};

const C_FORMAT_MAP = {
    'int': '%d', 'long': '%ld', 'double': '%f', 'float': '%f',
    'char': '%c', 'boolean': '%d', 'String': '%s',
};

function inferExprType(node) {
    if (!node) return 'int';
    switch (node.type) {
        case 'IntLit': return 'int';
        case 'DoubleLit': return 'double';
        case 'String': return 'String';
        case 'CharLit': return 'char';
        case 'Bool': return 'boolean';
        default: return node.javaType || 'int';
    }
}

function generateCode(ast, target = 'python') {
    let output = '';
    let indent = 0;

    function emit(str) { output += str; }
    function emitIndent() { emit('    '.repeat(indent)); }

    function genExpr(node) {
        if (!node) return;
        switch (node.type) {
            case 'IntLit':
                emit(String(node.value)); break;
            case 'DoubleLit':
                emit(String(node.value)); break;
            case 'String':
                emit(node.value); break;
            case 'CharLit':
                emit(`'${node.value}'`); break;
            case 'Bool':
                emit(target === 'python' ? (node.value ? 'True' : 'False') : (node.value ? '1' : '0'));
                break;
            case 'Identifier':
                if (node.name === 'null') {
                    emit(target === 'python' ? 'None' : 'NULL');
                } else {
                    emit(node.name);
                }
                break;
            case 'BinOp': {
                emit('(');
                genExpr(node.left);
                let op = node.op;
                if (target === 'python') {
                    if (op === '&&') op = ' and ';
                    else if (op === '||') op = ' or ';
                    else op = ` ${op} `;
                } else {
                    op = ` ${op} `;
                }
                emit(op);
                genExpr(node.right);
                emit(')');
                break;
            }
            case 'UnaryOp':
                if (node.op === '!') emit(target === 'python' ? 'not ' : '!');
                else if (node.op === '-') emit('-');
                else if (node.op === '~') emit('~');
                else if (node.op === '++' || node.op === '--') {
                    if (target === 'python') { genExpr(node.left); break; }
                    genExpr(node.left); emit(node.op); break;
                }
                emit('('); genExpr(node.left); emit(')');
                break;
            case 'FuncCall':
                emit(`${node.name}(`);
                if (node.left) {
                    node.left.items.forEach((arg, i) => {
                        if (i > 0) emit(', ');
                        genExpr(arg);
                    });
                }
                emit(')');
                break;
            case 'MethodCall':
                emit(`${node.name}(`);
                if (node.left) {
                    node.left.items.forEach((arg, i) => {
                        if (i > 0) emit(', ');
                        genExpr(arg);
                    });
                }
                emit(')');
                break;
            case 'ArrayAccess':
                emit(`${node.name}[`); genExpr(node.left); emit(']');
                break;
            case 'NewArray':
                if (target === 'python') {
                    emit('[0] * '); genExpr(node.left);
                } else {
                    const ct = C_TYPE_MAP[node.javaType] || 'int';
                    emit(`(${ct}*)calloc(`); genExpr(node.left); emit(`, sizeof(${ct}))`);
                }
                break;
            case 'Cast':
                if (target === 'python') {
                    emit(`${PY_TYPE_MAP[node.javaType] || node.javaType}(`);
                    genExpr(node.left); emit(')');
                } else {
                    emit(`(${C_TYPE_MAP[node.javaType] || node.javaType})(`);
                    genExpr(node.left); emit(')');
                }
                break;
        }
    }

    function genStmt(node) {
        if (!node) return;
        switch (node.type) {
            case 'Print':
                emitIndent();
                if (target === 'python') {
                    emit('print('); genExpr(node.left); emit(')\n');
                } else {
                    const et = inferExprType(node.left);
                    const fmt = C_FORMAT_MAP[et] || '%d';
                    emit(`printf("${fmt}\\n", `); genExpr(node.left); emit(');\n');
                }
                break;
            case 'VarDecl':
                emitIndent();
                if (target === 'python') {
                    if (node.left) {
                        emit(`${node.name} = `); genExpr(node.left); emit('\n');
                    } else {
                        const defaults = { 'int': '0', 'long': '0', 'double': '0.0', 'float': '0.0', 'boolean': 'False', 'char': "''", 'String': '""' };
                        emit(`${node.name} = ${defaults[node.javaType] || 'None'}\n`);
                    }
                } else {
                    const ct = C_TYPE_MAP[node.javaType] || 'int';
                    emit(`${ct} ${node.name}`);
                    if (node.left) { emit(' = '); genExpr(node.left); }
                    else {
                        if (node.javaType === 'String') emit(' = ""');
                        else emit(' = 0');
                    }
                    emit(';\n');
                }
                break;
            case 'Assign':
                emitIndent();
                emit(`${node.name} = `); genExpr(node.left);
                emit(target === 'python' ? '\n' : ';\n');
                break;
            case 'ClassDecl':
                if (target === 'python') {
                    emitIndent(); emit(`class ${node.name}:\n`);
                    indent++;
                    genBlock(node.body);
                    indent--;
                    emit('\n');
                } else {
                    emit(`/* class ${node.name} */\n`);
                    genBlock(node.body);
                }
                break;
            case 'MethodDecl':
                if (target === 'python') {
                    emitIndent();
                    if (node.name === 'main' && node.isStatic) {
                        emit('def main():\n');
                        indent++; genBlock(node.body); indent--;
                        emit('\n'); emitIndent();
                        emit('if __name__ == "__main__":\n');
                        indent++; emitIndent(); emit('main()\n'); indent--;
                    } else {
                        emit(`def ${node.name}(`);
                        if (node.left) emit(node.left.items.map(p => p.name).join(', '));
                        emit('):\n');
                        indent++; genBlock(node.body); indent--;
                        emit('\n');
                    }
                } else {
                    emitIndent();
                    const ct = C_TYPE_MAP[node.returnType] || 'int';
                    emit(`${ct} ${node.name}(`);
                    if (node.name === 'main' && node.isStatic) {
                        emit('int argc, char *argv[]');
                    } else if (node.left) {
                        emit(node.left.items.map(p => `${C_TYPE_MAP[p.javaType] || 'int'} ${p.name}`).join(', '));
                    }
                    emit(') {\n');
                    indent++; genBlock(node.body);
                    if (node.name === 'main') { emitIndent(); emit('return 0;\n'); }
                    indent--;
                    emitIndent(); emit('}\n\n');
                }
                break;
            case 'If':
                emitIndent();
                if (target === 'python') {
                    emit('if '); genExpr(node.left); emit(':\n');
                    indent++; genBlock(node.body); indent--;
                    if (node.right) {
                        if (node.right.type === 'If') {
                            emitIndent(); emit('el');
                            genStmt(node.right);
                        } else {
                            emitIndent(); emit('else:\n');
                            indent++; genBlock(node.right); indent--;
                        }
                    }
                } else {
                    emit('if ('); genExpr(node.left); emit(') {\n');
                    indent++; genBlock(node.body); indent--;
                    emitIndent(); emit('}');
                    if (node.right) {
                        if (node.right.type === 'If') {
                            emit(' else '); genStmt(node.right);
                        } else {
                            emit(' else {\n');
                            indent++; genBlock(node.right); indent--;
                            emitIndent(); emit('}');
                        }
                    }
                    emit('\n');
                }
                break;
            case 'While':
                emitIndent();
                if (target === 'python') {
                    emit('while '); genExpr(node.left); emit(':\n');
                    indent++; genBlock(node.body); indent--;
                } else {
                    emit('while ('); genExpr(node.left); emit(') {\n');
                    indent++; genBlock(node.body); indent--;
                    emitIndent(); emit('}\n');
                }
                break;
            case 'For':
                emitIndent();
                if (target === 'python') {
                    // Emit init then while
                    if (node.init) {
                        if (node.init.type === 'VarDecl') {
                            emit(`${node.init.name} = `);
                            if (node.init.left) genExpr(node.init.left);
                            else emit('0');
                            emit('\n');
                        } else if (node.init.type === 'Assign') {
                            emit(`${node.init.name} = `); genExpr(node.init.left);
                            emit('\n');
                        }
                    }
                    emitIndent(); emit('while '); genExpr(node.left); emit(':\n');
                    indent++; genBlock(node.body);
                    if (node.update) {
                        emitIndent();
                        if (node.update.type === 'Assign') {
                            emit(`${node.update.name} = `); genExpr(node.update.left);
                        }
                        emit('\n');
                    }
                    indent--;
                } else {
                    emit('for (');
                    if (node.init) {
                        if (node.init.type === 'VarDecl') {
                            const ct = C_TYPE_MAP[node.init.javaType] || 'int';
                            emit(`${ct} ${node.init.name} = `);
                            if (node.init.left) genExpr(node.init.left);
                            else emit('0');
                        } else if (node.init.type === 'Assign') {
                            emit(`${node.init.name} = `); genExpr(node.init.left);
                        }
                    }
                    emit('; '); genExpr(node.left); emit('; ');
                    if (node.update) {
                        if (node.update.type === 'Assign') {
                            emit(`${node.update.name} = `); genExpr(node.update.left);
                        }
                    }
                    emit(') {\n');
                    indent++; genBlock(node.body); indent--;
                    emitIndent(); emit('}\n');
                }
                break;
            case 'Return':
                emitIndent();
                if (node.left) {
                    emit('return '); genExpr(node.left);
                } else {
                    emit('return');
                }
                emit(target === 'python' ? '\n' : ';\n');
                break;
            case 'ExprStmt':
                emitIndent(); genExpr(node.left);
                emit(target === 'python' ? '\n' : ';\n');
                break;
        }
    }

    function genBlock(node) {
        if (!node) return;
        if (node.type === 'StmtList' || node.type === 'Program') {
            node.items.forEach(genStmt);
        } else {
            genStmt(node);
        }
    }

    // Header for C
    if (target === 'c') emit('#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n\n');

    // Process AST
    const items = ast.items || [];
    const hasClass = items.some(s => s.type === 'ClassDecl');

    if (hasClass) {
        for (const item of items) {
            if (item.type === 'ClassDecl' && item.body && item.body.items) {
                // Non-main methods first
                item.body.items.filter(m => m.type === 'MethodDecl' && m.name !== 'main').forEach(genStmt);
                // Static fields
                item.body.items.filter(m => m.type === 'VarDecl' && m.isStatic).forEach(genStmt);
                // Main last
                item.body.items.filter(m => m.type === 'MethodDecl' && m.name === 'main').forEach(genStmt);
            } else {
                genStmt(item);
            }
        }
    } else {
        // No class wrapper
        const methods = items.filter(s => s.type === 'MethodDecl');
        const nonMethods = items.filter(s => s.type !== 'MethodDecl');
        methods.forEach(genStmt);
        if (target === 'c' && nonMethods.length > 0) {
            emit('int main() {\n');
            indent = 1;
            nonMethods.forEach(genStmt);
            emit('    return 0;\n}\n');
        } else {
            nonMethods.forEach(genStmt);
        }
    }

    return output;
}

// ═══════════════════════════════════════════
// MAIN ENTRY POINT
// ═══════════════════════════════════════════

function transpile(code, target = 'python') {
    try {
        const tokens = tokenize(code);
        const parser = new Parser(tokens);
        const ast = parser.parse();
        const { errors, symbols } = semanticAnalyze(ast);

        let output = null;
        if (errors.length === 0) {
            output = generateCode(ast, target);
        }

        return {
            success: errors.length === 0,
            tokens: tokens.filter(t => t.type !== TOKEN_TYPES.EOF).map(t => ({
                type: t.type,
                value: t.value,
                line: t.line,
            })),
            ast,
            symbols: symbols.map(s => ({
                name: s.name,
                type: s.type,
                javaType: s.javaType,
                params: s.paramCount,
                line: s.line,
            })),
            errors,
            output,
        };
    } catch (err) {
        const lineMatch = err.message.match(/line (\d+)/);
        const line = lineMatch ? parseInt(lineMatch[1]) : 0;
        return {
            success: false,
            tokens: [],
            ast: null,
            symbols: [],
            errors: [{ line, message: err.message }],
            output: null,
        };
    }
}

module.exports = { transpile, tokenize, TOKEN_TYPES };
