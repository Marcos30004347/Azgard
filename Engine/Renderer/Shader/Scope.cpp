#include <malloc.h>
#include <string.h>

#include "Scope.hpp"

Scope* initScope() {
    Scope* s = (Scope*)calloc(1, sizeof(Scope));
    s->function_definitions = nullptr;
    s->functions_definitions_count = 0;

    s->variable_definitions = nullptr;
    s->variable_definitions_count = 0;

    return s;
}

AST* scopeAddFunctionDefinition(Scope* scope, AST* node) {
  
    if(scope->function_definitions == nullptr) {
        scope->functions_definitions_count = 1;
        scope->function_definitions = (AST**)calloc(1, sizeof(AST*));
    } else {
        scope->function_definitions = (AST**)realloc(scope->function_definitions, sizeof(AST*) * scope->functions_definitions_count + 1);
        scope->functions_definitions_count += 1;
    }

    scope->function_definitions[scope->functions_definitions_count - 1] = node;
    return node;
}

AST* scopeGetFunctionDefinition(Scope* scope, const char* fname) {
    for(int i=0; i<scope->functions_definitions_count; i++) {
        if(strcmp(scope->function_definitions[i]->function_name, fname) == 0) {
            return scope->function_definitions[i];
        }
    }

    return nullptr;
}

AST* scopeAddVariableDefinition(Scope* scope, AST* node) {
    if(scope->variable_definitions == nullptr) {
        scope->variable_definitions = (AST**)calloc(1, sizeof(AST*));
        scope->variable_definitions[0] = node;
        scope->variable_definitions_count = 1;
        return node;
    }

    scope->variable_definitions = (AST**)realloc(
        scope->variable_definitions,
        scope->variable_definitions_count * sizeof(AST*)
    );

    scope->variable_definitions_count += 1;
    scope->variable_definitions[scope->variable_definitions_count - 1] = node;

    return node;
}

AST* scopeGetVariableDefinition(Scope* scope, const char* vname) {
    for(int i=0; i<scope->variable_definitions_count; i++) {
        if(strcmp(scope->variable_definitions[i]->var_def_name, vname) == 0) {
            return scope->variable_definitions[i];
        }
    }

    return nullptr;
}

