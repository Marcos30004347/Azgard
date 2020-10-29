#include "AST.hpp"

#ifndef SCOPE_H
#define SCOPE_H

struct Scope {
    AST** function_definitions;
    unsigned int functions_definitions_count;

    AST** variable_definitions;
    unsigned int variable_definitions_count;
};

Scope* initScope();

AST* scopeAddFunctionDefinition(Scope* scope, AST* node);
AST* scopeGetFunctionDefinition(Scope* scope, const char* fname);

AST* scopeAddVariableDefinition(Scope* scope, AST* node);
AST* scopeGetVariableDefinition(Scope* scope, const char* vname);

#endif
