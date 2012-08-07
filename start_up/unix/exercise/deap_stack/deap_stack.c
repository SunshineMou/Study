/*!
 * \file	deap_stack.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-04 08:36:17
 */
#include <stdio.h>

int  a = 0;                 //全局初始化区   全局区（静态区）-->static
char *p1;                   //全局未初始化区

int main(int argc, char* argv[])
{
    int    b;                //栈
    char   s[] = "abc";      //栈
    char   *p2;              //栈
    char   *p3 = "123456";   //p3在栈上， “123456”在常量区
    static int  c = 0;       //全局（静态）初始化区
    p1 = (char *)malloc(10); //分配的来的10和20字节的区域就在堆区
    p2 = (char *)malloc(20);
     
    strcpy(p1, "123456");    // 123456放在常量区，编译器可能会将它与p3所指向的“123456”优化成一个地方
    return 0;
}

