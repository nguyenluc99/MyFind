#include "stack_tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// https://stackoverflow.com/questions/22575940/getopt-not-included-implicit-declaration-of-function-getopt

extern int status;
int
main(int argc, char *argv[])
{
    char* dirName = argv[1];
    status = 0;
    // printf("SEARCHING FOR  %s\n", dirName);
    AbstractSyntaxTree* condition = buildAST(argc, argv);
    if(status == 1)
        return 1;
    searchDirectory(dirName, condition);
    if(status == 1)
        return 1;

    return 0;
}
