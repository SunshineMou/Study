/*!
 * \file	fstat.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-17 09:59:52
 */

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        printf("Usage: fstat.out file");
        exit(0);
    }    
    int fd;
    fd=open(argv[1],O_RDONLY);
    struct stat buf;
    char *type;
    printf( "%s:    ", argv[1] );
    if ( fstat(fd, &buf) < 0 ) 
        printf("fstat error!\n");
    if ( S_ISREG(buf.st_mode) )  
        type = "regular";
    else if ( S_ISDIR(buf.st_mode) ) 
        type = "directory";
    else if ( S_ISCHR(buf.st_mode) )
        type = "character special";
    else if ( S_ISBLK(buf.st_mode) )
        type = "fifo";
    else if ( S_ISSOCK(buf.st_mode) ) 
        type = "symbolic link";    
    else
        type = " ** unknown mode";  
    printf( "%s\n", type );  
    exit (0);
}

