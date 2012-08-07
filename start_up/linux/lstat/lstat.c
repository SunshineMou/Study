/*!
 * \file	lstat.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-16 20:22:13
 */

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * This function use the 'latat' to detect the type of the file which you input;
 */ 
int main( int argc, char *argv[] ) 
{
    int i;
    struct stat buf;
    char   *type;        
    for ( i=1; i<argc; i++ )
    {
        printf( "%s:    ", argv[i] );
        if ( lstat(argv[i], &buf) < 0 ) 
        {
            continue;
        }
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
    }
    exit (0);
}
                                                                
