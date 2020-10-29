#include "Parser.hpp"
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

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
    if(parser->current_token->token_type == expected_token_type) {
        parser->previous_token = parser->current_token;
        parser->current_token = lexerGetNextToken(parser->lexex);
    } else {
        printf(
            "unexpected token! '%s', with type %i!",
            parser->current_token->value,
            parser->current_token->token_type
        );
        throw;
    }
}

AST* parserParser(Parser* parser, Scope* scope) {
    return parseStatments(parser, scope);
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
        case Token::type::ID: return parseId(parser, scope);
        default: break;
    }
    
    return initAST(AST::type::NO_OP);
}

// Parse all statements
AST* parseStatments(Parser* parser, Scope* scope) {
    AST* compound = initAST(AST::type::AST_COMPOUND);
    compound->scope = scope;
    compound->compound_value = (AST**)calloc(1, sizeof(AST*));

    AST* statement = parseStatment(parser, scope);
    statement->scope = scope;

    compound->compound_value[0] = statement;
    compound->compound_size += 1;


    while(parser->current_token->token_type == Token::type::SEMICOLON) {
        parserEat(parser, Token::type::SEMICOLON);
    
        AST* statement = parseStatment(parser, scope);
        compound->compound_size += 1;
        
        compound->compound_value = (AST**)realloc(
            compound->compound_value,
            compound->compound_size * sizeof(AST)
        );
        
        compound->compound_value[ compound->compound_size - 1] = statement;
    } 

    return compound;
}

AST* parseExpresion(Parser* parser, Scope* scope) {
    
    switch (parser->current_token->token_type) {
        case Token::type::STRING: return parseString(parser, scope);
        case Token::type::ID: return parseId(parser, scope);
        default: break;
    }
}

AST* parseFactor(Parser* parser, Scope* scope) {

}

AST* parseTerm(Parser* parser, Scope* scope) {

}

AST* parseFunctionCall(Parser* parser, Scope* scope) {
    AST* func_call = initAST(AST::type::AST_FUNCTION_CALL);

    func_call->func_call_name = parser->previous_token->value;
    func_call->func_call_arguments = (AST**)calloc(1, sizeof(AST*));

    parserEat(parser, Token::type::OPEN_PARENTESIS);

    AST* expression = parseExpresion(parser, scope);

    func_call->func_call_arguments[0] = expression;
    func_call->func_call_arguments_count += 1;


    while(parser->current_token->token_type == Token::type::COMMA) {
        parserEat(parser, Token::type::COMMA);
    
        AST* expression = parseExpresion(parser, scope);
        func_call->func_call_arguments_count += 1;
        
        func_call->compound_value = (AST**)realloc(
            func_call->func_call_arguments,
            func_call->func_call_arguments_count * sizeof(AST)
        );
        
        func_call->compound_value[ func_call->compound_size - 1] = expression;
    } 

    parserEat(parser, Token::type::CLOSE_PARENTESIS);

    func_call->scope = scope;
    return func_call;
}


AST* parseString(Parser* parser, Scope* scope) {
    AST* ast = initAST(AST::type::AST_STRING);
    ast->string_value = parser->current_token->value;
    parserEat(parser, Token::type::STRING);
    ast->scope = scope;
    return ast;
}

AST* parseVariable(Parser* parser, Scope* scope) {
    parserEat(parser, Token::type::ID);

    if(parser->current_token->token_type == Token::type::OPEN_PARENTESIS) {
        return parseFunctionCall(parser, scope);
    }

    AST* ast_var = initAST(AST::type::AST_VARIABLE);
    ast_var->var_name = parser->current_token->value;
    ast_var->scope = scope;
    return ast_var;
}

AST* parseVariableDefinition(Parser* parser, Scope* scope) {

    parserEat(parser, Token::type::ID);
    char* var_name = parser->current_token->value;
    parserEat(parser, Token::type::EQUALS);
    parserEat(parser, Token::type::ID);

    AST* var_value = parseExpresion(parser, scope);

    AST* var_def = initAST(AST::type::AST_VARIABLE_DEFINITION);

    var_def->var_def_name = var_name;
    var_def->var_def_value = var_value;

    var_def->scope = scope;
    return var_def;
}


AST* parseFunctionDefinition(Parser* parser, Scope* scope) {
    AST* function_definition = initAST(AST::type::AST_FUNCTION_DEFINITION);
    function_definition->scope = scope; // maybe a new scope will be appropriate

    parserEat(parser, Token::type::ID); // function Keyword

    char* function_name = parser->current_token->value;
    // function_definition->function_name = function_name;

    function_definition->function_name = (char*)calloc(strlen(function_name) + 1, sizeof(char));
    strcpy(function_definition->function_name, function_name);
    function_definition->function_name[strlen(function_name)] = '\0';



    parserEat(parser, Token::type::ID); // function name
    parserEat(parser, Token::type::OPEN_PARENTESIS); // (
    
    // Alrguments
    
    AST* arg = parseVariable(parser, scope);
    function_definition->function_arguments_count = 1;
    function_definition->function_arguments = (AST**)calloc(
        1,
        sizeof(AST*)
    );
    function_definition->func_call_arguments[0] = arg;

    while (parser->current_token->token_type == Token::type::COMMA) {
        AST* arg = parseVariable(parser, scope);
        
        function_definition->function_arguments_count += 1;

        function_definition->function_arguments = (AST**)realloc(
            function_definition->function_arguments,
            function_definition->function_arguments_count*sizeof(AST*)
        );
        
        function_definition->func_call_arguments[function_definition->func_call_arguments_count - 1] = arg;
    }
    

    parserEat(parser, Token::type::CLOSE_PARENTESIS); // )
    parserEat(parser, Token::type::OPEN_BRACKET); // {
    
    // Body
    function_definition->function_body = parseStatments(parser, scope);

    parserEat(parser, Token::type::CLOSE_BRACKET); // }

    return function_definition;
}