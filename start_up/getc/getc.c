/*!
 * \file	getc.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-17 14:17:12
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define MAXLINE 1101

/*
 * The function could read bytes from stdin--terminal and save the bytes into a txt file;
 */
int main(int argc, char* argv[])
{
    char buf[MAXLINE];
    FILE *point;
    point=fopen(argv[1],"a+b");
    char *string=":exit";
    int i=0;
    while(fgets(buf,MAXLINE,stdin)!=NULL)
    {
        for(i=0;buf[i]==*string && string[i]!='\0';i++,string++)
            if(*(string+1)=='\0')
            {
                fclose(point);
                exit(0);
            }
        if(fputs(buf,point)==EOF)
        {
            printf("fputs error!\n");
            exit(0);
        }
    }
    exit(0);
}

