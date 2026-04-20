# Transpiler Makefile
# Requires: flex, bison, gcc

CC = gcc
CFLAGS = -Wall -g
FLEX = flex
BISON = bison

TARGET = transpiler

SRCS = ast.c symtab.c semantic.c codegen.c main.c
GENERATED = lex.yy.c parser.tab.c parser.tab.h

all: $(TARGET)

parser.tab.c parser.tab.h: parser.y
	$(BISON) -d parser.y

lex.yy.c: lexer.l parser.tab.h
	$(FLEX) lexer.l

$(TARGET): $(SRCS) lex.yy.c parser.tab.c
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) lex.yy.c parser.tab.c -lm

clean:
	rm -f $(TARGET) $(GENERATED)

# Windows variant (use with mingw32-make or similar)
win: parser.tab.c lex.yy.c
	$(CC) $(CFLAGS) -o $(TARGET).exe $(SRCS) lex.yy.c parser.tab.c

.PHONY: all clean win
