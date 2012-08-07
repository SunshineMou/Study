/*!
 * \file	struct.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-29 15:46:35
 */
#include <stdio.h>

typedef struct test_struct{
    int  number;
    char letter;
}iStruct;

int main(int argc, char* argv[])
{
    iStruct a = {1, 'a'};
    iStruct b;
    b = a;
    
    printf("%d\n", b.number);

    if(&(a.number) == &(b.number))
        printf("OK!\n");
     
    return 0;
}

