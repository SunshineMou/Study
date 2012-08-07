/*!
 * \file	puzzle2.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-07 16:57:44
 */

#include <stdio.h>

int main(int argc, char* argv[])
{
    int a[][3]    = {1, 2, 3, 4, 5, 6, 7};
    int (*ptr)[3] = a;

    printf("%d %d ", (*ptr)[1], (*ptr)[2]);

    ++ptr;
    printf("%d %d\n", (*ptr)[1], (*ptr)[2]);

    ++ptr;
    printf("%d %d\n", (*ptr)[0], (*ptr)[0]);

    return 0;     
}

