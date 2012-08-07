/*!
 * \file	func_list.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-08 14:44:24
 */
#include <stdio.h>

void Exchange3(int &x, int &y){
    int tmp = x;
    x = y;
    y = tmp;
    printf("x = %d, y = %d\n", x, y);
}

int main(int argc, char* argv[])
{
    int a = 4;
    int b = 6;
    Exchange3(a, b);
    printf("a = %d, b = %d\n", a, b);
     
    return 0;
}

