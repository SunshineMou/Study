/*!
 * \file	endian.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-03 14:54:54
 */
#include <stdio.h>

int  isBigEndian()
{
    union
    {
        int  i;
        char  c;
    }test;

    test.c = 2;

    return  test.i != 2;
}

int main(int argc, char* argv[])
{
    if(isBigEndian())
       printf("Your computer is Big Endian!\n"); 
    printf("Your computer is Little Endian!\n"); 
    return 0;
}

