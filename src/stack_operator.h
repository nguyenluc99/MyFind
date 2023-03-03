#ifndef STACK_OPERATOR_H
#define STACK_OPERATOR_H

enum operator
{
    OR,
    AND
};

typedef struct NodeOperator
{
    enum operator val;
    struct NodeOperator *next;
} NodeOperator;

/* Struct represents OPERATORS */
typedef struct StackOperator
{
    NodeOperator *top;
} StackOperator;

void pushOperator(StackOperator *s, enum operator val);

enum operator popOperator(StackOperator *s);

void printStackOperator(StackOperator *s);

StackOperator *createStackOperator();

NodeOperator *createNodeOperator(enum operator val);

enum operator peekOperator(StackOperator *s);

int isEmptyOperator(StackOperator *s);

#endif
