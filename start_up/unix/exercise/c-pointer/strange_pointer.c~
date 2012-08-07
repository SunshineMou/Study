/*!
 * \file	strange_pointer.c
 * \brief   字符串常量的类型是“指向字符的指针”	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-13 15:27:18
 */
#include <stdio.h>

void binary_to_ascii(unsigned int value);

int main(int argc, char* argv[])
{
    printf("%c\n", *("xyz" + 1));
    
    printf("%c\n", *("xyz"));
    
    int value = 12;
    putchar("0123456789ABCDEF"[value%16]);
    printf("\n");

    binary_to_ascii(101);
    printf("\n");

    return 0;
}

void binary_to_ascii(unsigned int value){
    unsigned int quotient;

    quotient = value / 10;
    if(quotient != 0)
        binary_to_ascii(quotient);
    putchar(value % 10 + '0');
}

