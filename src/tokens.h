#ifndef TOKENS_H
#define TOKENS_H
enum {
	ID,
	DECL_ID,
	ARRAY,
	BOOL,
	CHAR,
	INT,
	REAL,
	RECORD,
	INT_CONST,
	REAL_CONST,
	STRING_CONST,
	_BEGIN,
	END,
	IF,
	THEN,
	ELSE,
	WHILE,
	DO,
	CONTINUE,
	EXIT,
	OF,
	PROGRAM,
	TYPE,
	VAR,
	CONST,
	FUNCTION,
	PROCEDURE,
	L_PAREN,
	R_PAREN,
	LS_BRACKET,
	RS_BRACKET,
	PERIOD,
	COMMA,
	SEMICOLON,
	COLON,
	RANGE,
	ASSIGN,
	UNREC,
	NOT,
	MULTIPLY,
	DIVIDE,
	DIV,
	MOD,
	AND,
	PLUS,
	MINUS,
	OR,
	EQUAL,
	NOT_EQUAL,
	LESS,
	LESS_OR_EQUAL,
	GREATER,
	GREATER_OR_EQUAL 
} tokens; 
#endif
