/*!
 * \file	fgets.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-07 19:16:57
 */
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char buf[200] = "";
    fgets(buf, sizeof(buf), stdin);
    printf("which you just input is:%s,the length is:%d\n", buf, strlen(buf));
    return 0;
}

