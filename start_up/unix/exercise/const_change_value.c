/*!
 * \file	const_change_value.c
 * \brief   通过强制转换，将地址赋予变量，再修改即可改变const常量值	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-04 13:50:54
 */
#include <stdio.h>

int main(int argc, char* argv[])
{
    const int a = 0;
    int   *p    = (int *)&a;
    /*int   *p    = &a;*/
    *p  = 100;

    printf("After the change, the value of 'a' is: %d\n", a); 
    return 0;
}

