/*!
 * \file	strange_print_3.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-17 17:08:39
 */
#include <stdio.h> 

int main() 
{
    int a=3, b = 5;

    printf(&a["Ya!Hello! how is this? %s\n"], &b["junk/super"]);
    printf(&a["WHAT%c%c%c  %c%c  %c !\n"], 1["this"], 2["beauty"],0["tool"],0["is"],3["sensitive"],4["CCCCCC"]);
    
    return 0; 
}

