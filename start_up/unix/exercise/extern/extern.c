/*!
 * \file	extern.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-08 10:58:25
 */
#include <stdio.h>

extern int global;
/*extern int new_printf(char* argv);*/
/*int new_printf(char* argv);*/

int main(int argc, char* argv[])
{
    if(global)
        printf("We can use the value of the global variable!\n");
    else
        printf("We can not use the value of the global variable!\n");

    new_printf("xiaodong");
    return 0;
}

