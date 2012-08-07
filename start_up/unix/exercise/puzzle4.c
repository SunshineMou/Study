/*!
 * \file	puzzle4.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-08 08:51:20
 */

#include <stdio.h>

int main(int argc, char* argv[])
{
    char   p;
    char   buf[10] = {1, 2, 3, 4, 5, 6, 9, 8};

    p = (buf +1)[5];
    printf("%d\n", p);
     
    return 0;
}

