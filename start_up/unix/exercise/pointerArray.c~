/*!
 * \file	pointerArray.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-23 17:14:06
 */

#include <stdio.h>

char* convert( unsigned long Value );

int main(int argc, char* argv[])
{
    int a[5]={0,1,2,3,4};
    int *p;
    p = (int *)(&a + 1);
    /*p = a + 1;*/
    printf("%d\n", *p);
    printf("%p\n", a);
    printf("%p\n", p);
    printf("%d\n", *(p-1));
    printf("%p\n", p-1);
    printf("1[a] is: %d\n", 1[a]);
    printf("%d\n", 3[a]);
    a[3] = "0tring"[0];
    printf("3[a] is:%c\n", 3[a]);
    printf("4[a] is:%d\n", 4[a]);
    char *pointer = convert(1000);
    printf("The result is: %s\n", pointer); 
    return 0;
}

char* convert( unsigned long Value ){
    static char Buffer[sizeof( unsigned long ) * 2 + 1];
    int i;
    for( i = sizeof( unsigned long ) * 2 - 1; i >= 0; --i ){
        Buffer[i] = "0123456789ABCDEF"[Value % 16];
        Value /= 16;
    }
    return Buffer;
}

 

