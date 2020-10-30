

#ifndef AST_H
#define AST_H

struct Scope;

struct AST {
    enum type {
        AST_VARIABLE,
        AST_VARIABLE_DEFINITION, // var t = 1
        AST_FUNCTION_CALL, // func()
        AST_STRING,
        AST_COMPOUND,
        NO_OP,
        AST_FUNCTION_DEFINITION,
    };

    type ast_type;

    // AST_FUNCTION_DEFINITION
    AST* func_definition_body;
    char* func_definition_name;
    AST** func_definition_arguments;
    unsigned int func_definition_arguments_count;

    // AST_FUNCTION_CALL
    char* func_call_name;
    AST** func_call_arguments;
    unsigned int func_call_arguments_count;

    // AST_VARIABLE_DEFINITION
    char* var_def_name;
    AST* var_def_value;

    // AST_VARIABLE
    char* var_name;

    // AST_STRING
    char* string_value;

    // AST_COMPOUND
    AST** compound_value;
    unsigned int compound_size;

    Scope* scope;
};  


AST* initAST(AST::type type);

void printAST(AST* root);
#endif