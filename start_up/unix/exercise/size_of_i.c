/*!
 * \file	size_of_i.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-17 16:20:47
 */
#include <stdio.h> 

int main() 
{ 
    int i; 
    i = 10; 
    printf("i : %d\n",i); 
    printf("sizeof(i++) is: %d\n",sizeof(i++)); 
    printf("i : %d\n",i); 

    return 0; 
}

