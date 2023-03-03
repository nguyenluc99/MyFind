#ifndef NODE_H
#define NODE_H
#include <stdlib.h>

int PRINTALLPATH;

// enum Operand
// {
//     NAME,
//     TYPE,
//     NEWER,
//     DELETE,
//     EXEC,
//     EXECDIR
// };

enum NodeType
{
    OPERATOR_OR,
    OPERATOR_AND,
    FILTER_NAME,
    FILTER_TYPE,
    FILTER_NEWER,
    FILTER_PRINT
};

int checkType(char* fullPath, char* cond);
int checkName(char* itemName, char* cond);
int checkNewer(char* examinedItem, char* givenItem);

#endif
