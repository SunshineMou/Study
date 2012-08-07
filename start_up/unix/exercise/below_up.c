/*!
 * \file	below_up.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-12 14:05:56
 */
#include <stdio.h>

int main(int argc, char* argv[])
{
    int i, a[10];

    printf("%p\n", &i);
    printf("%p\n", a+9);
    printf("%p\n", a);

    for(i = 1; i <= 10; i++){
        a[i] = 0;
        printf("Here!\n");
    }
     
    return 0;
}

