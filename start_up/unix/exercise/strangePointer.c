/*!
 * \file	strangePointer.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-14 19:57:39
 */
#include <stdio.h>

void *strangeReturn(){
    printf("The function return!");
    return((void *)1);
}

int main(int argc, char* argv[])
{
    void    *pointer;
    pointer = strangeReturn();
    printf("The result is:%d\n", (int)pointer);
    printf("The result is:%s\n", (void *)1);  /*段错误*/
     
    return 0;
}

