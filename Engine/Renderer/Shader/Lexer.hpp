
#ifndef LEXER_H
#define LEXER_H


struct Lexer {
    char* contents;
    unsigned int i;
    char c;
};

struct Token {

    enum type {
        ID,
        EQUALS,
        STRING,
        SEMICOLON,
        OPEN_PARENTESIS,
        CLOSE_PARENTESIS,
        OPEN_BRACKET,
        CLOSE_BRACKET,
        COMMA,
        PERIOD,
        TOKEN_EOF,
    };
    type token_type;
    char* value;
};


void lexerAdvance(Lexer* lex);
void lexerSkipWhitespace(Lexer* lex);

char* lexerGetCurrentCharAsString(Lexer* lex);

Lexer* initLexer(char* contents);

Token* initToken(Token::type type, char* value);
Token* lexerAdvanceWithToken(Lexer* lex, Token* tok);
Token* lexerCollectString(Lexer* lex);
Token* lexerCollectId(Lexer* lex);
Token* lexerGetNextToken(Lexer* lex);

#endif
