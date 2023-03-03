#include "stack_action.h"

#include <stdio.h>
#include <stdlib.h>

void pushAction(StackAction *s, Action* val)
{
    NodeAction *n = (NodeAction *)malloc(sizeof(NodeAction));
    n->val = val;
    n->next = s->top;
    s->top = n;
}

Action popAction(StackAction *s)
{
    if (s->top == NULL)
    {
        printf("Error: stack underflow\n");
        exit(1);
    }
    NodeAction *n = s->top;
    Action val = n->val;
    s->top = n->next;
    free(n);
    return val;
}

void printStackAction(StackAction *s)
{
    NodeAction *n = s->top;
    printf("actions:\n");
    while (n != NULL)
    {
        printf("{ type: %d, value: %s }\n", n->val.action, n->val.value);
        n = n->next;
    }
}

NodeAction *createNodeAction(Action val)
{
    NodeAction *n = (NodeAction *)malloc(sizeof(NodeAction));
    n->val = val;
    n->next = NULL;
    return n;
}

StackAction *createStackAction()
{
    StackAction *s = (StackAction *)malloc(sizeof(StackAction));
    s->top = NULL;
    return s;
}

int isEmptyAction(StackAction *s) { return s->top == NULL; }
