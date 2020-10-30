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


void printAST(AST* root) {
    if(root->ast_type == AST::type::AST_COMPOUND) {
        for(int i=0; i<root->compound_size; i++) {
            printAST(root->compound_value[i]);
        }
    }

    if(root->ast_type == AST::type::AST_STRING) {
        printf("AST STRING:\n");
        printf("String: '%s'\n", root->string_value);
        printf("\n");
    }

    if(root->ast_type == AST::type::AST_VARIABLE_DEFINITION) {
        printf("AST VARIABLE DEFINITION:\n");
        printf("variable name: '%s'\n", root->var_def_name);
        printf("variable value:'\n");
        printAST(root->var_def_value);
        printf("\n");
    }

    if(root->ast_type == AST::type::AST_VARIABLE) {
        printf("AST VARIABLE:\n");
        printf("variable name: %s\n", root->var_name);
        printf("\n");
    }

    if(root->ast_type == AST::type::AST_FUNCTION_DEFINITION) {
        printf("AST FUNCTION DEFINITION:\n");
        printf("func definition name: %s\n", root->func_definition_name);
        printf("func definition arguments:\n");
        for(int i=0;i< root->func_definition_arguments_count; i++) {
            printf("argument %u\n", i);
            printAST(root->func_definition_arguments[i]);
        }
        printAST(root->func_definition_body);
        printf("\n");
    }

    if(root->ast_type == AST::type::AST_FUNCTION_CALL) {
        printf("AST FUNCTION CALL:\n");
        printf("func call name: %s\n", root->func_call_name);
        printf("func call arguments: %u\n", root->func_call_arguments_count);
    
        for(int i=0;i<root->func_call_arguments_count; i++) {
            printf("@argument %u\n", i);
            printAST(root->func_call_arguments[i]);
        }
        printf("\n");
    }

}

