#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

struct lexer {
    char* contents;
    unsigned int i;
    char c;
};

struct token {

    enum type {
        ID,
        EQUALS,
        STRING,
        SEMICOLON,
        OPEN_PARENTESIS,
        CLOSE_PARENTESIS,
        OPEN_BRACKET,
        CLOSE_BRACKET,
    };
    type tp;
    char* value;
};

lexer* initLexer(char* contents) {
    lexer* lex = (lexer*)calloc(1, sizeof(lexer));
    lex->contents = contents;
    lex->i = 0;
    lex->c = lex->contents[lex->c];
    return lex;
}

token* initToken(token::type type, char* value) {
    token* tok = (token*)calloc(1, sizeof(token));
    tok->value = value;
    tok->tp = type;
    return tok;
}

void lexerAdvance(lexer* lex) {
    if(lex->c != '\0' && lex->i < strlen(lex->contents)) {
        lex->i +=1;
        lex->c = lex->contents[lex->i];
    }
}

void lexerSkipWhitespace(lexer* lex) {
    while(lex->c == ' ' || lex->c == 10) {
        lexerAdvance(lex);
    }
}

token* lexerAdvanceWithToken(lexer* lex, token* tok) {
    lexerAdvance(lex);
    return tok;
}

char* lexerGetCurrentCharAsString(lexer* lex) {
    char* str = (char*)calloc(2, sizeof(char));
    str[0] = lex->c;
    str[1] = '\0';
    return str;
}

token* lexerCollectString(lexer* lex) {
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
    return initToken(token::type::STRING, value);
}

token* lexerCollectId(lexer* lex) {
    char* value = (char*)calloc(1, sizeof(char));
    value[0] = '\0';
    while(isalnum(lex->c)) {
        char* s = lexerGetCurrentCharAsString(lex);
        value = (char*)realloc(value, (strlen(value) + strlen(s) + 1)*sizeof(char));
        strcat(value, s);
        lexerAdvance(lex);
    }

    return initToken(token::type::ID, value);
}

token* lexerGetNextToken(lexer* lex) {
    while(lex->c != '\0' && lex->i < strlen(lex->contents)) {
        if(lex->c == ' ' || lex->c == 10) lexerSkipWhitespace(lex);
        if(isalnum(lex->c)) return lexerCollectId(lex);
        if(lex->c == '"') return lexerCollectString(lex);
        switch (lex->c) {
            case '=': return lexerAdvanceWithToken(lex, initToken(token::type::EQUALS, lexerGetCurrentCharAsString(lex))); break;
            case '(': return lexerAdvanceWithToken(lex, initToken(token::type::OPEN_PARENTESIS, lexerGetCurrentCharAsString(lex))); break;
            case ')': return lexerAdvanceWithToken(lex, initToken(token::type::CLOSE_PARENTESIS, lexerGetCurrentCharAsString(lex))); break;
            case ';': return lexerAdvanceWithToken(lex, initToken(token::type::SEMICOLON, lexerGetCurrentCharAsString(lex))); break;
            case '{': return lexerAdvanceWithToken(lex, initToken(token::type::OPEN_BRACKET, lexerGetCurrentCharAsString(lex))); break;
            case '}': return lexerAdvanceWithToken(lex, initToken(token::type::CLOSE_BRACKET, lexerGetCurrentCharAsString(lex))); break;
            default: break;
        }
    }
    return nullptr;
}
