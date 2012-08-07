/*!
 * \file	sizeof.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-05 14:49:09
 */
#include <stdio.h>

#define Handle 1024
int main(int argc, char* argv[])
{
    int size[16];

    printf("The result is:%d\n", sizeof(char)*Handle);
    printf("The result is:%d\n", sizeof(size));

    char pointer[5] = "a";
    char *test = pointer;
    int result = 0;
    
    /*下面的语句是错误的，根本不会编译通过*/
    result = sizeof(int) * test;
    printf("Result ...%d\n", result);

    return 0;
}

