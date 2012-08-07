/*!
 * \file	pionter.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-01 11:24:02
 */
#include <stdio.h>

int main(int argc, char* argv[])
{
    char amessage[] = "Now is the time";
    char *pmessage  = "Now is the time";
    pmessage = amessage;
    pmessage[1] = 'p';
    /**(pmessage + 5) = 'e';*/
    printf("The 'amessage' string is:%s\n", amessage);
    printf("The 'pmessage' string is:%s\n", pmessage);
    return 0;
}

