#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <fnmatch.h>
#include <sys/stat.h>

#include "node.h"

int status = 0;

int
checkType(char* fullPath, char* cond)
{   
    struct stat file;

    if (lstat(fullPath, &file) == -1)
        fprintf(stderr, "myfind: Failed to read file %s\n", fullPath);

    if (strcmp(cond, "b") == 0) // special block
        return S_ISBLK(file.st_mode);
    if (strcmp(cond, "c") == 0) // special character
        return S_ISCHR(file.st_mode);
    if (strcmp(cond, "d") == 0) // directories
        return S_ISDIR(file.st_mode);
    if (strcmp(cond, "f") == 0) // regular file
        return S_ISREG(file.st_mode);
    if (strcmp(cond, "l") == 0) // symbolics link
        return S_ISLNK(file.st_mode);
    if (strcmp(cond, "p") == 0) // named pipelines (FIFO)
        return S_ISFIFO(file.st_mode);
    if (strcmp(cond, "s") == 0) // socket
        return S_ISSOCK(file.st_mode);

    return 0; // default means NOT MATCH
}

int
checkName(char* itemName, char* cond)
{
    int res;
    
    res = fnmatch(cond, itemName, FNM_PATHNAME);
    if (res == FNM_NOMATCH)
        return 0;

    return 1;
}

int
checkNewer(char* examinedItem, char* givenItem)
{
    struct stat examined, given;
    time_t examinedTime, givenTime;
    
    stat(examinedItem, &examined);
    stat(givenItem, &given);
    examinedTime  = examined.st_mtime; // TODO: change this to your proper time value to use nanosecond level.
    givenTime  = given.st_mtime;
    if (examinedTime > givenTime)
        return 1;

    return 0;
}
