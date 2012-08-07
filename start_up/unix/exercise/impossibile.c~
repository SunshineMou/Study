/*!
 * \file	impossibile.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-23 08:42:42
 */
#include <stdio.h>

int *kidding(){
    int a = 5;
    return &a;
}

int main(int argc, char* argv[])
{
    int *p;
    p = kidding();
    printf("The return value is: %d\n", *p);

    *p = 7;
    printf("The current value is: %d\n", *p);

    return 0;
}

