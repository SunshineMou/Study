/*!
 * \file	strchar.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-15 16:15:26
 */

#include <stdio.h>

const char * strrchr ( const char * str, int character );
const char * strchr ( const char * str, int character );

int main(int argc, char* argv[])
{
    char *point;
    point=strchr(argv[1],'s');
    printf("The string form the position 's' is:%d\n",point-argv[1]+1);
    return 0;
}

const char * strchr ( const char * str, int character )
{
    int i=0;
    while(*(str+i)!=character)
    {
        i++;
        if(*(str+i)=='\0')
            return NULL;
    }
    return (str+i);
}

const char * strrchr ( const char * str, int character )
{
    int i=0;
    int position=0;
    do
    {
        if(*(str+i)==character)
        {
            if(position<i)
                position=i;
        }
        i++;
        if(*(str+i)=='\0')
            return (str+position);
    }while(*(str+i)!='\0');
    return NULL;
}
