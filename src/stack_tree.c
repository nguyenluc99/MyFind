#include "stack_tree.h"
#include <getopt.h>

extern int status;

AbstractSyntaxTree*
popStackTree(StackTree* stackTree)
{
    AbstractSyntaxTree* top;

    if (isEmpty(stackTree))
    {
        printf("CANNOT POP FROM EMPTY STACK!");
    }
    top = stackTree->top;
    stackTree->top = top->prev;
    stackTree->size --;
    /*
     * Job done, we will add this AST to the bigger one.
     * So, we dont care about what its previous is.
     */ 
    top->prev = 0; 

    return top;
}

void
pushStackTree(StackTree* stackTree, AbstractSyntaxTree* ast)
{
    ast->prev = stackTree->top;
    stackTree->top = ast;
    stackTree->size ++;
}

StackTree*
createStackTree()
{
    StackTree* st;
    
    st = (StackTree*) malloc(sizeof(StackTree));
    st->size = 0;
    st->top = NULL;

    return st;
}

AbstractSyntaxTree*
createTree(enum NodeType type)
{
    AbstractSyntaxTree* ast;
    
    ast = (AbstractSyntaxTree*) malloc(sizeof(AbstractSyntaxTree));
    ast->type = type;

    return ast;
}

void
mergeTops(StackTree* stackTree, enum NodeType type)
{
    AbstractSyntaxTree *ast, *left, *right;
    
    ast = createTree(type);
    left = popStackTree(stackTree);
    right = popStackTree(stackTree);
    
    ast->left = left;
    ast->right = right;
    ast->condition = "";
    
    pushStackTree(stackTree, ast);
}

void
parseStackToAST(StackTree* stackTree, enum NodeType op)
{
    /*
     * The elements stored in OPERANDS STACK are actually many 
     * small AST. They will be combined into a singly large AST.
     */
    if (stackTree->size < 2)
        return;
    /*
     * Without parenthesis, there cannot be any OR nested in some AND.
     * So, just process when there is an AND.
     */
    if (op == OPERATOR_AND || op == OPERATOR_OR)
        /* merge two small trees into a bigger tree */
        mergeTops(stackTree, op);
    else
        exit(1); /* third OPERATOR is not implemented yet */
}

void
addFilterToStackTree(StackTree* stackTree, char* filter, enum NodeType filterType)
{
    /* only accept FILTER here */
    AbstractSyntaxTree *ast;
    
    ast = createTree(filterType);
    ast->left = NULL;
    ast->right = NULL;
    ast->prev = NULL;
    ast->condition = filter;

    pushStackTree(stackTree, ast);
}

AbstractSyntaxTree *
buildAST(int argc, char* argv[])
{
    char            c;
    const char     *short_options = "0:1:2345poa";
    static struct option    long_options[] = {
        {"name",        required_argument,  NULL,  '0' },
        {"type",        required_argument,  NULL,  '1' },
        {"newer",       required_argument,  NULL,  '2' },
        {"delete",      no_argument,        NULL,  '3' },
        {"exec",        no_argument,        NULL,  '4' },
        {"execdir",     no_argument,        NULL,  '5' },
        {"print",       no_argument,        NULL,  'p' },
        {"or",          no_argument,        NULL,  'o' },
        {"and",         no_argument,        NULL,  'a' },
        {0,             0,                  NULL,   0  }
    };
    StackTree      *stackTree = createStackTree();
    int             previousIsAnd = 0;
    int             canParseWithoutAnd = 0;
    
    PRINTALLPATH = 0;

    while((c=getopt_long_only(argc-1, argv+1, short_options, long_options, NULL)) != -1)
    {
        switch(c)
        {
            case '0':
                {
                    addFilterToStackTree(stackTree, optarg, FILTER_NAME);
                    /* 
                     * In case of no OPERATOR* added, or the previous OPERATOR
                     * is indeed an AND, just priotize the AND by parsing two
                     * items at the top using an AND right now.
                     */
                    if (previousIsAnd || canParseWithoutAnd)
                        parseStackToAST(stackTree, OPERATOR_AND);
                    canParseWithoutAnd = 1;
                }
                break;
            case '1':
                {
                    optarg[1] = 0; // we only need an character actually
                    addFilterToStackTree(stackTree, optarg, FILTER_TYPE);
                    if (previousIsAnd || canParseWithoutAnd)
                        parseStackToAST(stackTree, OPERATOR_AND);
                    canParseWithoutAnd = 1;
                }
                break;
            case '2':
                {
                    addFilterToStackTree(stackTree, optarg, FILTER_NEWER);
                    if (previousIsAnd || canParseWithoutAnd)
                        parseStackToAST(stackTree, OPERATOR_AND);
                    canParseWithoutAnd = 1;
                }
                break;
            case '3':
            case '4':
            case '5':
                // TODO
                break;
            case 'p':
                PRINTALLPATH = 1;
                break;
            case 'o':
                previousIsAnd = 0;
                canParseWithoutAnd = 0;
                break;
            case 'a':
                /*
                 * OPERATOR_AND is inserted, so on the next parameter, we can
                 * combine two nodes into a single AbstractSyntaxTree.
                 */
                previousIsAnd = 1; 
                break;

            case '?':
                // fprintf(stderr, "myfind: Failed to parse option %c\n", c);
                status=1;
                // exit(1);
                break;
        }
    }

    while(stackTree->size != 1)
        /* 
         * all the rest are treated as OR operator.
         */
        parseStackToAST(stackTree, OPERATOR_OR);

    return stackTree->top;
}
