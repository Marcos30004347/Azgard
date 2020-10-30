#include "Lexer.hpp"

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <vector>


Lexer* initLexer(char* contents) {
    Lexer* lex = (Lexer*)calloc(1, sizeof(Lexer));
    lex->contents = contents;
    lex->i = 0;
    lex->c = lex->contents[lex->c];
    return lex;
}

Token* initToken(Token::TokenType type, char* value) {
    Token* tok = (Token*)calloc(1, sizeof(Token));
    tok->value = value;
    tok->token_type = type;
    return tok;
}

void lexerAdvance(Lexer* lex) {
    if(lex->c != '\0' && lex->i < strlen(lex->contents)) {
        lex->i +=1;
        lex->c = lex->contents[lex->i];
    }
}

void lexerSkipWhitespace(Lexer* lex) {
    while(lex->c == ' ' || lex->c == 10) {
        lexerAdvance(lex);
    }
}

Token* lexerAdvanceWithToken(Lexer* lex, Token* tok) {
    lexerAdvance(lex);
    return tok;
}

char* lexerGetCurrentCharAsString(Lexer* lex) {
    char* str = (char*)calloc(2, sizeof(char));
    str[0] = lex->c;
    str[1] = '\0';
    return str;
}

Token* lexerCollectString(Lexer* lex) {
    lexerAdvance(lex);
    char* value = (char*)calloc(1, sizeof(char));
    value[0] = '\0';
    while(lex->c != '"') {
        char* s = lexerGetCurrentCharAsString(lex);
        value = (char*)realloc(value, (strlen(value) + strlen(s) + 1)*sizeof(char));
        lexerAdvance(lex);
        strcat(value, s);
    }

    lexerAdvance(lex); // advance because of '"'
    return initToken(Token::TokenType::STRING, value);
}

Token* lexerCollectId(Lexer* lex) {

    char* value = (char*)calloc(1, sizeof(char));
    value[0] = '\0';

    while(isalnum(lex->c)) {
        char* s = lexerGetCurrentCharAsString(lex);
        value = (char*)realloc(value, (strlen(value) + strlen(s) + 1)*sizeof(char));
        strcat(value, s);
        lexerAdvance(lex);
    }

    return initToken(Token::TokenType::ID, value);
}

Token* lexerGetNextToken(Lexer* lex) {
    while(lex->c != '\0' && lex->i < strlen(lex->contents)) {
        if(lex->c == ' ' || lex->c == 10) lexerSkipWhitespace(lex);
        if(isalnum(lex->c)) return lexerCollectId(lex);
        if(lex->c == '"') return lexerCollectString(lex);
        switch (lex->c) {
            case '=': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::EQUALS, lexerGetCurrentCharAsString(lex))); break;
            case '(': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::OPEN_PARENTESIS, lexerGetCurrentCharAsString(lex))); break;
            case ')': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::CLOSE_PARENTESIS, lexerGetCurrentCharAsString(lex))); break;
            case ';': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::SEMICOLON, lexerGetCurrentCharAsString(lex))); break;
            case '{': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::OPEN_BRACKET, lexerGetCurrentCharAsString(lex))); break;
            case '}': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::CLOSE_BRACKET, lexerGetCurrentCharAsString(lex))); break;
            case ',': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::COMMA, lexerGetCurrentCharAsString(lex))); break;
            case '.': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::PERIOD, lexerGetCurrentCharAsString(lex))); break;
            default: break;
        }
    }
    char* nullString = new char[1];
    nullString[0] = '\0';

    return initToken(Token::TokenType::TOKEN_EOF, nullString);
}
