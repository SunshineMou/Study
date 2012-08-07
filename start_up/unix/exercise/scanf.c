/*!
 * \file	scanf.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-18 08:20:28
 */
#include <stdio.h>

int main(int argc, char* argv[])
{
    char  dummy[80];
    printf("Enter a string:\n");
    scanf("%[^r]", dummy);
    printf("%s\n",dummy);
     
    return 0;
}

