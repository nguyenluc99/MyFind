#ifndef STACK_ACTION_H
#define STACK_ACTION_H

enum action
{
    NAME,
    TYPE,
    NEWER,
    PRINT
};

typedef struct
{
    enum action action;
    char *value;
} Action;

typedef struct nodeAction
{
    Action *val;
    struct nodeAction *next;
} NodeAction;

/* Struct represents OPERANDS */
typedef struct StackAction
{
    NodeAction *top;
} StackAction;

void pushAction(StackAction* s, Action* val);

Action popAction(StackAction* s);

void printStackAction(StackAction* s);

NodeAction *createNodeAction(Action val);

StackAction *createStackAction();

int isEmptyAction(StackAction* s);

#endif
