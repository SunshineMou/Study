/*!
 * \file	important.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-07 16:36:26
 */
#include <stdio.h>

int x = 7;

int magic(){
    if(x)
    {
        int x = 10;
        printf("[%s]In the if(true) environment! The value of x is: %d\n", \
                __func__, x);
    }

    int x = 11;

    /*extern int x;*/
    x = 8;
    printf("[%s]Out the if(true) environment! The value of x is: %d\n",    \
            __func__, x);
    return x;
}

int main(int argc, char* argv[])
{
    int y = 0;

    y = magic();
    printf("x is:%d\n", y);
    printf("x is:%d\n", x);
     
    return 0;
}

