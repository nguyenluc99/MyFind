#include "stack_operator.h"

#include <stdio.h>
#include <stdlib.h>

void pushOperator(StackOperator *s, enum operator val)
{
    NodeOperator *n = (NodeOperator *)malloc(sizeof(NodeOperator));
    n->val = val;
    n->next = s->top;
    s->top = n;
}

// enum operator popOperator(StackOperator *s)
// {
//     if (s->top == NULL)
//     {
//         printf("Error: stack underflow\n");
//         exit(1);
//     }
//     NodeOperator *n = s->top;
//     enum operator val = n->val;
//     s->top = n->next;
//     free(n);
//     return val;
// }

void printStackOperator(StackOperator *s)
{
    NodeOperator *n = s->top;
    printf("operators:\n");
    while (n != NULL)
    {
        if (n->val == or)
        {
            printf("or\n");
        }
        else if (n->val == and)
        {
            printf("and\n");
        }
        n = n->next;
    }
}

StackOperator *createStackOperator()
{
    StackOperator *s = (StackOperator *)malloc(sizeof(StackOperator));
    s->top = NULL;
    return s;
}

NodeOperator *createNodeOperator(enum operator val)
{
    NodeOperator *n = (NodeOperator *)malloc(sizeof(NodeOperator));
    n->val = val;
    n->next = NULL;
    return n;
}

enum operator peekOperator(StackOperator *s)
{
    if (s->top == NULL)
    {
        printf("Error: stack underflow\n");
        exit(1);
    }
    return s->top->val;
}

int isEmptyOperator(StackOperator *s) { return s->top == NULL; }
