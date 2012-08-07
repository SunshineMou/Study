/*!
 * \file	puzzle_3.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-18 10:07:54
 */
#include <stdio.h>

enum { false, true};

int main(int argc, char* argv[])
{
    int  i = 1;

    do{
        printf(" %d\n", i);
        i++;

        if(i < 15)
            continue;
    }while(false);
     
    return 0;
}

