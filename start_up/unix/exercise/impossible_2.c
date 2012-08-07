/*!
 * \file	impossible_2.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-23 09:46:22
 */
#include <stdio.h>

void foo_a(){
    /*volatile int array[10];*/
    int array[10];
    int i;
    for(i = 0; i < 10; i++){
        array[i] = i;
        printf("%d, ", array[i]);
    }
    printf("\n");
}

void foo_b(){
    int array[12];
    int i;
    for(i = 0; i < 12; i++)
        printf("%d, ", array[i]);
    printf("\n");
}

int main(int argc, char* argv[])
{
    foo_a();
    foo_b();
     
    return 0;
}

