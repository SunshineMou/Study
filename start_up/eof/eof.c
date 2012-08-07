/*!
 * \file	test.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-19 10:03:29
 */

#include <stdio.h>

/*!
 * \brief This function is used to display the value of EOF:  Ctrl +d ;
 *
 * \param argc
 * \param argv[]
 *
 * \return 
 */
int main(int argc, char* argv[])
{
    int c;
    printf("Please input the char:  ");    
    while((c=getchar()) != EOF)
        putchar(c);
    printf("The value of EOF is:%d\n",EOF);    
    return 0;
}

