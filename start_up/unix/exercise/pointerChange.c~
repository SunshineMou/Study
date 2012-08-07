/*!
 * \file	pointerChange.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-01 17:09:37
 */
#include <stdio.h>
#include <stdlib.h>
void swap(int  *pa, int *pb)
{
    int temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

int main(int argc, char* argv[])
{
    char a[]="BACD"; 
    swap((int*)&a[0],(int*)&a[1]);
    printf("after swap:\n");
    printf("%s\n",a); 
    sleep(5); 
    return 0;
}

