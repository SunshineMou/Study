/*!
 * \file	puzzle3.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-07 17:22:01
 */

#include <stdio.h>

int main(int argc, char* argv[])
{
    int  i = 3;
    int  j, z;

    j = sizeof(++i);   /*此处对于i的操作会产生未知的行为，所以i会保持原来的值不变*/

    z = sizeof(int);

    printf("i = %d j = %d z = %d\n", i, j, z);
     
    return 0;
}

