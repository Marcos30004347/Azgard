#include "AST.hpp"

#ifndef VISITOR_H
#define VISITOR_H

struct Visitor {};

Visitor* initVisitor();
AST* visit(Visitor* visitor, AST* node);
AST* visitVariable(Visitor* visitor, AST* node);
AST* visitVariableDefinition(Visitor* visitor, AST* node);
AST* visitFunctionCall(Visitor* visitor, AST* node);
AST* visitString(Visitor* visitor, AST* node);
AST* visitCompound(Visitor* visitor, AST* node);
AST* visitFunctionDefinition(Visitor* visitor, AST* node);

#endif