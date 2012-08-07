/*!
 * \file	printUsername.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-25 16:54:11
 */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    char   *username;
    username = getlogin();
    printf("The username is: %s\n", username);     
    return 0;
}

