/*!
 * \file	null.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-12 11:19:33
 */
#include <stdio.h>

int main(int argc, char* argv[])
{
    char *p = NULL;
    char *q = "xiaodong";
    char test[] = "xiaodong";

    /*p = test;*/

    printf("%s\n", (char *)0);
    printf("%s\n", q);
     
    return 0;
}

