/*!
 * \file	ttyname.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-02 11:29:12
 */

#include <stdio.h>

int main(int argc, char* argv[])
{
    char   ttyname[L_ctermid];
    if(ctermid(ttyname) != NULL)
        printf("The terminal name is: %s\n", ttyname);
    return 0;
}

