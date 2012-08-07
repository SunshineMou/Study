/*!
 * \file	strange_print_2.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-17 16:43:22
 */
#include <stdio.h>

#define PrintInt(expr) printf("%s : %d\n",#expr,(expr))


int main()
{
    int y = 100;
    int *p;
    p = malloc(sizeof(int));
    *p = 10;
    y = y / *p; /*dividing y by *p */
    PrintInt(y);
    return 0;
}

