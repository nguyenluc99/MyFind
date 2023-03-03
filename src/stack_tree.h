#ifndef STACK_TREE_H
#define STACK_TREE_H

#include "node.h"
#include "AST.h"

#include <stdio.h>
#include <stdlib.h>

#define isEmpty(T) (T->size == 0)

/* Struct represents all tree being parsed */
typedef struct StackTree
{
    AbstractSyntaxTree *top;
    int size;
} StackTree;

AbstractSyntaxTree* popStackTree(StackTree* stackTree);

void pushStackTree(StackTree* stackTree, AbstractSyntaxTree* ast);

StackTree* createStackTree();

// void mergeTops(StackTree* stackTree, enum NodeType type);
// AbstractSyntaxTree* createTree(enum NodeType type);
AbstractSyntaxTree *buildAST(int argc, char* argv[]);

#endif
