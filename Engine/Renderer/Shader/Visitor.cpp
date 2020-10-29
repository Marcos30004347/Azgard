#include "Visitor.hpp"
#include "Scope.hpp"

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <vector>

Visitor* initVisitor() {
    Visitor* v = (Visitor*)calloc(1, sizeof(Visitor));
    return v;
}

AST* visit(Visitor* visitor, AST* node) {
    if(!node) return initAST(AST::type::NO_OP);

    switch (node->ast_type) {
        case AST::type::AST_COMPOUND            : return visitCompound(visitor, node);
        case AST::type::AST_VARIABLE            : return visitVariable(visitor, node);
        case AST::type::AST_STRING              : return visitString(visitor, node);
        case AST::type::AST_FUNCTION_CALL       : return visitFunctionCall(visitor, node);
        case AST::type::AST_VARIABLE_DEFINITION : return visitVariableDefinition(visitor, node);
        case AST::type::AST_FUNCTION_DEFINITION : return visitFunctionDefinition(visitor, node);

        default: printf("Uncaught statement of type %i!", node->ast_type); return initAST(AST::type::NO_OP);
    }

    return nullptr;
}

AST* visitVariable(Visitor* visitor, AST* node) {
    return scopeGetVariableDefinition(node->scope, node->var_def_name);
}

AST* visitVariableDefinition(Visitor* visitor, AST* node) {
    return scopeAddFunctionDefinition(node->scope, node);
}

static AST* buildInPrint(Visitor* visitor, AST** args, int arg_size) {
    for(int i=0; i< arg_size; i++) {
        AST* visited = visit(visitor, args[i]);
        switch (visited->ast_type) {
            case AST::type::AST_STRING: printf("visited arg: %s\n", visited->string_value); return;
            default: break;
        }
    }

    return initAST(AST::type::NO_OP);
}

AST* visitFunctionCall(Visitor* visitor, AST* node) {

    if(strcmp(node->func_call_name, "buildInPrint")) {
        buildInPrint(visitor, node->func_call_arguments, node->func_call_arguments_count);
    }

    // get function definition
    AST* func = scopeGetFunctionDefinition(node->scope, node->func_call_name);

    if(func == nullptr) {
        printf("Undefined method %s\n!", node->func_call_name);
        throw;
    }
    
    // parse arguments
    for(int i=0; i<func->function_arguments_count; i++) {
        AST* ast_var_definition = initAST(AST::type::AST_VARIABLE_DEFINITION);
        
        AST* var = func->function_arguments[i];
    
        ast_var_definition->var_def_name = (char*)malloc(sizeof(char)*(strlen(var->var_name) + 1));
        strcpy(ast_var_definition->var_def_name, var->var_name);
        ast_var_definition->var_def_name[strlen(var->var_name)] = '\0';
    
        AST* value = node->func_call_arguments[i];
        ast_var_definition->var_def_value = value;

        // Add var to scope
        scopeAddFunctionDefinition(
            func->scope,
            ast_var_definition
        );
    }


    visit(visitor, func->function_body);

}

AST* visitString(Visitor* visitor, AST* node) {
    return node;
}

AST* visitCompound(Visitor* visitor, AST* node) {
    for(int i=0; i<node->compound_size; i++) {
        visit(visitor, node->compound_value[i]);
    }

    return initAST(AST::type::NO_OP);
}

AST* visitFunctionDefinition(Visitor* visitor, AST* node) {
    return scopeAddFunctionDefinition(node->scope, node);
}




