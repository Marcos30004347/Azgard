#include "AST.hpp"
#include <malloc.h>

AST* initAST(AST::type type) {
    // AST
    AST* ast = (AST*)calloc(1, sizeof(AST));
    ast->ast_type = type;
    ast->scope = nullptr;

    // AST_FUNCTION_DEFINITION
    ast->func_definition_body = nullptr;
    ast->func_definition_name = nullptr;
    ast->func_definition_arguments = nullptr;
    ast->func_definition_arguments_count = 0;

    // AST_VARIABLE_DEFINITION
    ast->var_def_name = nullptr;
    ast->var_def_value = nullptr;

    // AST_VARIABLE
    ast->var_name = nullptr;

    // AST_FUNCTION_CALL
    ast->func_call_name = nullptr;
    ast->func_call_arguments = nullptr;
    ast->func_call_arguments_count = 0;

    // AST_STRING
    ast->string_value = nullptr;

    // AST_COMPOUND
    AST** compound_value = nullptr;
    unsigned int compound_size = 0;
    
    return ast;
}


