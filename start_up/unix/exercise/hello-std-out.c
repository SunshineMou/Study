/*!
 * \file	hello-std-out.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-17 14:05:26
 */
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int i;
    for(i = 0; i < 2; i++){
        fprintf(stdout, "hello-std-out ");
        fprintf(stderr, "hello-std-err ");
        sleep(1);
    }
     
    return 0;
}

