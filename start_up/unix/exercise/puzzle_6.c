/*!
 * \file	puzzle_6.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-18 11:30:31
 */
#include <stdio.h>

int x = 7;

/*!
 * \brief  强制转换的使用
 */
void foo(){
    printf("y is:%ld\n", (unsigned long) (-1/8));
    printf("y is:%ld\n", (unsigned long) -1/8);
}

/*!
 * \brief  实现局部变量屏蔽全局变量 
 *
 * \return 
 */
int int_value_1(){
    extern int x;
    {
        int x = 5;
        printf("[%s]The value of x is: %d\n", __func__, x);
        return x;
    }
}

/*!
 * \brief  实现全局变量屏蔽局部变量 
 *
 * \return 
 */
int int_value_2(){
    int x = 5;
    {
        extern int x;
        printf("[%s]The value of x is: %d\n", __func__, x);
        return x;
    }
}

/*!
 * \brief  局部变量的作用范围 
 *
 * \return 
 */
int int_value_3(){
    if(x)
    {
        int x = 10;
        printf("[%s]The value of x is: %d\n", __func__, x);
    }
    printf("[%s]The value of x is: %d\n", __func__, x);
    return x;
}

int main(int argc, char* argv[])
{
    int y;

    y = int_value_1();
    printf("x is:%d\n", y);
    printf("x is:%d\n", x);
     
    y = int_value_2();
    printf("x is:%d\n", y);
    printf("x is:%d\n", x);
     
    y = int_value_3();
    printf("x is:%d\n", y);
    printf("x is:%d\n", x);

    foo();

    return 0;
}

