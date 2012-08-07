/*!
 * \file	c_deep_1.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-02 13:34:49
 */

#include <stdio.h>

void f(void)
{
    static int a = 3;
    static int b;
    int c = 0;
    ++a; ++b; ++c;
    printf("a=%d\n", a);
    printf("b=%d\n", b);
    printf("c=%d\n", c);
}

int main(void)
{
    f();
    f();
    f();
}
