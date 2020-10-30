
#include "AST.hpp"
#include "Lexer.hpp"
#include "Scope.hpp"

#ifndef PARSER_H
#define PARSER_H


struct Parser {
    Lexer* lexex;
    Scope* scope;
    Token* current_token;
    Token* previous_token;
};
Parser* initParser(Lexer* lexer);

void parserEat(Parser* parser, int expected_token_type);
AST* parseStatment(Parser* parser, Scope* scope);
AST* parseStatments(Parser* parser, Scope* scope);
AST* parse(Parser* parser);
AST* parseExpresion(Parser* parser, Scope* scope);
AST* parseFactor(Parser* parser, Scope* scope);
AST* parseTerm(Parser* parser, Scope* scope);
AST* parseFunctionCall(Parser* parser, Scope* scope);
AST* parseFunctionDefinition(Parser* parser, Scope* scope);
AST* parseVariable(Parser* parser, Scope* scope);

// var varName = expression
AST* parseVariableDefinition(Parser* parser, Scope* scope);

AST* parseInt(Parser* parser, Scope* scope);
AST* parseString(Parser* parser, Scope* scope);


#endif
