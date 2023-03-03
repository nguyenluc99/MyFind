#include "AST.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fnmatch.h>
#include <sys/stat.h>
#include <dirent.h> 

extern int PRINTALLPATH;
extern int status;

int
checkMatch(char* itemFullPath, struct dirent *dir, AbstractSyntaxTree *condition)
{
    int left;

    switch(condition->type)
    {
        case OPERATOR_OR:
            left = checkMatch(itemFullPath, dir, condition->left);
            if (left) return 1;
            return checkMatch(itemFullPath, dir, condition->right);
        case OPERATOR_AND:
            left = checkMatch(itemFullPath, dir, condition->left);
            if (!left) return 0;
            return checkMatch(itemFullPath, dir, condition->right);
        case FILTER_NAME:
            return checkName(dir->d_name, condition->condition);
        case FILTER_TYPE:
            return checkType(itemFullPath, condition->condition);
        case FILTER_NEWER:
            return checkNewer(itemFullPath, condition->condition);
        case FILTER_PRINT:
        default:
            break;
    }

    return 0;
}

void
searchDirectory(char* currentDirName, AbstractSyntaxTree* treeCondition)
{
    struct dirent *dir;
    DIR         *d;

    d = opendir(currentDirName);
    while ((dir = readdir(d)) != NULL) {
        char *itemFullPath;

        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
            continue;

        itemFullPath = (char*) malloc(strlen(currentDirName) + strlen(dir->d_name) + 2);
        sprintf(itemFullPath, "%s/%s", currentDirName, dir->d_name);

        if (checkMatch(itemFullPath, dir, treeCondition))
            printf("%s\n", itemFullPath);
        
        if (dir->d_type == DT_DIR)
        {
            searchDirectory(itemFullPath, treeCondition);
        }
        free(itemFullPath);
        if (dir->d_type == DT_UNKNOWN)
        {
            status = 1;
            // TODO
        }
    }
    closedir(d);
}
