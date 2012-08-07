/*!
 * \file	byte_length.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-14 08:59:49
 */
#include <stdio.h>
#include <limits.h>

void dead_cycle_1();
void dead_cycle_2();

int main(int argc, char* argv[])
{
    dead_cycle_1();
    dead_cycle_2();
     
    return 0;
}

/*
 *  UCHAR_MAX是limits中用于表示当前编译环境unsigned char最大值的宏;
 *  C在limits.h（C++则为climits）头文件中使用了一个宏CHAR_BIT，用于指示当前编译环境的byte的二进制宽度。
 *  一段高移植性的代码不应该基于一个byte为8bit的假设
 */

/*!
 * \brief 这个循环可以保证在任何标准的环境中都是死循环；
 */
void dead_cycle_1(){
    unsigned char a[UCHAR_MAX];
    unsigned char i;
    for(i = 0; i <= UCHAR_MAX; ++i){
        a[i] = i;
        printf("%d\n", i);
    }
}

/*!
 * \brief 如果一个byte不是8位，这个循环就不一定是个死循环；
 */
void dead_cycle_2(){
    unsigned char a[255];
    unsigned char i;
    printf("%d\n", CHAR_BIT);
    printf("%d\n", UCHAR_MAX);
    for(i = 0; i <= 255; ++i){
        a[i] = i;
        printf("%d\n", i);
    }
}
