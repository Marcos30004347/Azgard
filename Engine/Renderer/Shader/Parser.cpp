#include "Parser.hpp"
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

const char* TokenTypeNames[] = {
    "'identifier'",
    "=",
    "'string'",
    ";",
    "(",
    ")",
    "{",
    "}",
    ",",
    ".",
    "EOF",
};


static Scope* getNodeScope(Parser* parser, AST* node) {
    return node->scope == nullptr ? parser->scope : node->scope;
}

Parser* initParser(Lexer* lexer) {
    Parser* p = (Parser*)calloc(1, sizeof(Parser));
    p->scope = initScope();
    p->lexex = lexer;

    p->current_token = lexerGetNextToken(lexer);
    p->previous_token = p->current_token;
    return p;
}


void parserEat(Parser* parser, int expected_token_type) {
    printf("#Eating: %s\n", TokenTypeNames[expected_token_type]);
    printf("#Value: %s\n", parser->current_token->value);

    if(parser->current_token->token_type == expected_token_type) {
        parser->previous_token = parser->current_token;
        parser->current_token = lexerGetNextToken(parser->lexex);

    } else {
        printf(
            "unexpected token! '%s' with type '%s' expecting '%s'!",
            parser->current_token->value,
            TokenTypeNames[parser->current_token->token_type],
            TokenTypeNames[expected_token_type]
        );
        exit(-1);
    }
}

AST* parse(Parser* parser) {
    return parseStatments(parser, parser->scope);
}

AST* parseId(Parser* parser, Scope* scope) {

    if(strcmp(parser->current_token->value, "var") == 0) {
        return parseVariableDefinition(parser, scope);
    } else
    if(strcmp(parser->current_token->value, "function") == 0) {
        return parseFunctionDefinition(parser, scope);
    }

    return parseVariable(parser, scope);
}

AST* parseStatment(Parser* parser, Scope* scope) {
    switch (parser->current_token->token_type) {
        case Token::TokenType::ID: return parseId(parser, scope);
        default: break;
    }
    
    return initAST(AST::type::NO_OP);
}

// Parse all statements
AST* parseStatments(Parser* parser, Scope* scope) {
    printf("***Parsing Statements...\n");

    AST* compound = initAST(AST::type::AST_COMPOUND);
    compound->scope = scope;
    compound->compound_value = (AST**)calloc(1, sizeof(AST*));

    AST* statement = parseStatment(parser, scope);
    statement->scope = scope;

    compound->compound_value[0] = statement;
    compound->compound_size += 1;


    while(parser->current_token->token_type == Token::TokenType::SEMICOLON) {
        parserEat(parser, Token::TokenType::SEMICOLON);
    
        AST* statement = parseStatment(parser, scope);
        compound->compound_size += 1;
        
        compound->compound_value = (AST**)realloc(
            compound->compound_value,
            compound->compound_size * sizeof(AST)
        );
        
        compound->compound_value[ compound->compound_size - 1] = statement;
    } 
    printf("***Parsed Statements!\n");

    return compound;
}

AST* parseExpresion(Parser* parser, Scope* scope) {
    printf("=====>Parsing Expression...\n");

    switch (parser->current_token->token_type) {
        case Token::TokenType::STRING: return parseString(parser, scope);
        case Token::TokenType::ID: return parseId(parser, scope);
        default: break;
    }

    return initAST(AST::type::NO_OP);
}



AST* parseFactor(Parser* parser, Scope* scope) {
    printf("Not valid yet!");
    exit(-1);
}

AST* parseTerm(Parser* parser, Scope* scope) {
    printf("Not valid yet!");
    exit(-1);
}

AST* parseFunctionCall(Parser* parser, Scope* scope) {
    AST* func_call = initAST(AST::type::AST_FUNCTION_CALL);
    printf("***Parsing Function call...\n");

    func_call->func_call_name = parser->previous_token->value;
    func_call->func_call_arguments = (AST**)calloc(1, sizeof(AST*));

    parserEat(parser, Token::TokenType::OPEN_PARENTESIS);

    AST* expression = parseExpresion(parser, scope);

    func_call->func_call_arguments[0] = expression;
    func_call->func_call_arguments_count += 1;


    while(parser->current_token->token_type == Token::TokenType::COMMA) {
        parserEat(parser, Token::TokenType::COMMA);

        AST* expression = parseExpresion(parser, scope);
        func_call->func_call_arguments_count += 1;
        printf("    Function Argument:\n");
        
        func_call->compound_value = (AST**)realloc(
            func_call->func_call_arguments,
            func_call->func_call_arguments_count * sizeof(AST)
        );
        printf("    Function Argument.\n");
        
        func_call->compound_value[ func_call->compound_size - 1] = expression;
    } 

    parserEat(parser, Token::TokenType::CLOSE_PARENTESIS);

    // func_call->scope = scope;
    func_call->scope = initScope();
    printf("Function scope: %p\n", func_call->scope);

    printf("***Parsed Function call!\n");
    return func_call;
}


AST* parseString(Parser* parser, Scope* scope) {
    printf("***Parsing String...\n");
    AST* ast = initAST(AST::type::AST_STRING);
    ast->string_value = parser->current_token->value;

    printf("String value: %s\n", ast->string_value);

    parserEat(parser, Token::TokenType::STRING);
    ast->scope = scope;
    printf("String scope: %p\n", ast->scope);
    printf("***Parsed String!\n");
    return ast;
}

AST* parseVariable(Parser* parser, Scope* scope) {

    parserEat(parser, Token::TokenType::ID);

    if(parser->current_token->token_type == Token::TokenType::OPEN_PARENTESIS) {
        return parseFunctionCall(parser, scope);
    }

    printf("***Parsing Variable ...\n");
    AST* ast_var = initAST(AST::type::AST_VARIABLE);
    ast_var->var_name = parser->previous_token->value;
    printf("Variable name: '%s'!\n", ast_var->var_name);
    ast_var->scope = scope;

    printf("Variable Scope: '%p'!\n", ast_var->scope);
    printf("***Parsed Variable!\n");
    return ast_var;
}

AST* parseVariableDefinition(Parser* parser, Scope* scope) {
    printf("***Parsing Variable definition...\n");
    parserEat(parser, Token::TokenType::ID); // var word

    char* var_name = parser->current_token->value;
    parserEat(parser, Token::TokenType::ID);

    printf("Variable Name: %s\n", var_name);

    parserEat(parser, Token::TokenType::EQUALS);

    AST* var_value = parseExpresion(parser, scope);

    AST* var_def = initAST(AST::type::AST_VARIABLE_DEFINITION);

    var_def->var_def_name = var_name;
    var_def->var_def_value = var_value;

    var_def->scope = scope;

    printf("Variable Scope: %p\n", scope);

    printf("***Parsed Variable definition!\n");

    return var_def;
}


AST* parseFunctionDefinition(Parser* parser, Scope* scope) {
    printf("***Parsing Function definition...\n");

    AST* function_definition = initAST(AST::type::AST_FUNCTION_DEFINITION);
    function_definition->scope = scope; // maybe a new scope will be appropriate

    parserEat(parser, Token::TokenType::ID); // function Keyword

    char* func_definition_name = parser->current_token->value;

    function_definition->func_definition_name = (char*)calloc(strlen(func_definition_name) + 1, sizeof(char));
    strcpy(function_definition->func_definition_name, func_definition_name);
    function_definition->func_definition_name[strlen(func_definition_name)] = '\0';



    parserEat(parser, Token::TokenType::ID); // function name
    parserEat(parser, Token::TokenType::OPEN_PARENTESIS); // (
    
    // Arguments
    
    AST* arg = parseVariable(parser, scope);

    function_definition->func_definition_arguments_count = 1;
    function_definition->func_definition_arguments = (AST**)calloc(
        1,
        sizeof(AST*)
    );

    function_definition->func_definition_arguments[0] = arg;

    while (parser->current_token->token_type == Token::TokenType::COMMA) {
        parserEat(parser, Token::TokenType::COMMA);

        AST* arg = parseVariable(parser, scope);
        
        function_definition->func_definition_arguments_count += 1;

        function_definition->func_definition_arguments = (AST**)realloc(
            function_definition->func_definition_arguments,
            function_definition->func_definition_arguments_count*sizeof(AST*)
        );
        
        function_definition->func_definition_arguments[function_definition->func_definition_arguments_count - 1] = arg;
    }
    

    parserEat(parser, Token::TokenType::CLOSE_PARENTESIS); // )
    parserEat(parser, Token::TokenType::OPEN_BRACKET); // {
    
    // Body
    function_definition->func_definition_body = parseStatments(parser, scope);

    parserEat(parser, Token::TokenType::CLOSE_BRACKET); // }

    printf("***Parsed Function definition!\n");
    return function_definition;
}