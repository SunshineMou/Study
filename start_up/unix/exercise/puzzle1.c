/*!
 * \file	puzzle1.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-07 16:47:37
 */

#include <stdio.h>

int main(int argc, char* argv[])
{
    int    a, b, c, d;
    a = 3;
    b = 5;
    c = a, b;
    d = (a, b);
    printf("c = %d\n", c);
    printf("d = %d\n", d);
     
    return 0;
}

