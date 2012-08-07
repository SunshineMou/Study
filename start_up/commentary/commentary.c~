/*!
 * \file	commentary.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-22 09:58:14
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int cancle_commentary(char *file);

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        printf("Usage:commentary.out file.c;\n");
        exit(-1);
    }
    if(cancle_commentary(argv[1]) == 1)
        printf("Success;\n");
    else
        printf("Fali;\n");
    exit(0);
}

/*!
 * \brief This function is used to cancle the commentary content of the file;
 *
 * \param file
 *
 * \return 
 */
int cancle_commentary(char *file)
{ 
    FILE *fd;
    FILE *fd2;
    FILE *tmp;
    int i = 0;
    int j = 0;
    int find_mask = 0;
    char buffer[1111];
    if((tmp = tmpfile()) == NULL)
        printf("Creat tmpfile fail;\n");
    if((fd = fopen(file , "r+")) == NULL)
    {
        printf("Open %s error;\n",file);
        return 0;
    }
    while(fgets(buffer , 1111 , fd) != NULL)
    {
        if(find_mask == 0)
        {
            for(i=0; buffer[i] != '\n';i++)
            {
                if(buffer[i] == '/' && buffer[i+1] == '*')
                {
                    if(i == 0)
                    {
                        find_mask = 2;
                        break;
                    }
                    else
                    {
                        find_mask = 1;
                        for(j=0; buffer[i+j] != '\n'; j++)
                        {
                            buffer[i+j] = ' ';
                            if(buffer[i+j+2] == '*' && buffer[i+j+3] == '/')
                            {
                                find_mask = 0;
                                buffer[i+j+1] = ' ';
                                buffer[i+j+2] = ' ';
                                buffer[i+j+3] = ' ';
                                break;
                            }
                        }
                    }
                }
            }
            if(find_mask == 2)
                ;
            else
                fputs(buffer, tmp);
        }
        if(find_mask == 1 || find_mask == 2)
        {
            for(i=0; buffer[i] != '\n'; i++)
            {
                if(buffer[i] == '*' && buffer[i+1] == '/')
                {
                    buffer[i] = ' ';
                    buffer[i+1] = ' ';
                    find_mask = 0;
                    break;
                }
                buffer[i] = ' ';
            }
            if(find_mask == 0)
                fputs(buffer, tmp);
        }
    }
    fclose(fd);
    fd2 = fopen(file,"w");
    fseek(tmp, 0, SEEK_SET);
    while(fgets(buffer, 1111, tmp) != NULL)
        fputs(buffer, fd);
    return 1;
}
