/*!
 * \file	is_it.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-09 14:28:50
 */
#include <stdio.h>

int main(int argc, char* argv[])
{
    char test[2][10] = {"xiaodong", "sunshine"};
    char (*p)[10] = test;
    
    int a = 1;
    const int *p_int;
    p_int = &a;
    /**p_int = 3;*/

    a = 2;

    printf("a = %d\n", *p_int);

    printf("%s\n", p); 
    return 0;
}

