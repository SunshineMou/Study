/*!
 * \file	define.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-13 08:08:04
 */
#include <stdio.h>

#define GUESS int i; int j; int k;

#define PREFIX "/usr/share/"
#define PATH PREFIX "path"

typedef struct exercise_struct{
    GUESS
}iStruct;

int main(int argc, char* argv[])
{
    int length;
    int int_to_unsigned;

    length = sizeof(iStruct);
    int_to_unsigned = sizeof(length);
    int_to_unsigned == 2 ? printf("unsigned int ...\n") : printf("int ...\n");
    printf("The length is: %d\n", length);
    length = sizeof(int) + (int)length;
    printf("The length is: %d\n", length);

    printf("%s\n", PATH);
    printf("%s\n", "/usr/share/" "path");

    return 0;
}

