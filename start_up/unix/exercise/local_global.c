/*!
 * \file	local_global.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-01 09:22:24
 */

#include <stdio.h>

int value = 10;

void func();

int main(int argc, char* argv[])
{
    func();     
    return 0;
}

void func(){
    int *p = &value;
    int value = 5;
    printf("The local 'value' is: %d\n", value);
    /*printf("The local 'value' is: %d\n", ::value);*/
    printf("The global 'value' is: %d\n", *p);
}

