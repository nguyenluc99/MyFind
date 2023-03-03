#ifndef AST_H
#define AST_H
#include "node.h"

typedef struct AbstractSyntaxTree
{
    enum NodeType type;                 /* Type of node in the tree */
    struct AbstractSyntaxTree *left;    /* right node in case of OPERATOR type */
    struct AbstractSyntaxTree *right;   /* right node in case of OPERATOR type */
    char* condition;                    /* real condition used to filter in case of OPERAND */
    struct AbstractSyntaxTree *prev;    /* previous node while parsing stack */
} AbstractSyntaxTree;


void searchDirectory(char* directory, AbstractSyntaxTree* treeCondition);

#endif
