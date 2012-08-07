#include "stdio.h"
#include <fcntl.h>
#include <string.h>
void reverse(char string[]);
void reverse_str(char str[], int start, int end);

int
main(int argc,char *argv[])
{
    char string[] = "sunshine";
    reverse(string);
    printf("The reverse string is: %s\n",string);
    reverse_str(string, 2, 5);
    printf("The reverse string is: %s\n",string);
    return 1;
}

/*!
 * \brief Reverse the string which the given by the call function;
 *
 * \param string[]
 */
void reverse(char string[])
{
    int i=0;
    int j=0;
    for(i=0;string[i] != '\0';i++)
        ;
    char tmp;
    for(j = 0;j <= (i-1)/2; j++)
    {
        tmp=string[j];
        string[j]=string[i-j-1];
        string[i-j-1] = tmp;
    }   
}

/*!
 * \brief Reverse the branch string in the given string from location 'start' to 'end'; 
 *
 * \param str[]
 * \param start
 * \param end
 */
void reverse_str(char str[], int start, int end)
{
    int i = 1;
    char tmp;
    tmp = str[start];
    str[start] = str[end];
    str[end] = tmp;
    for(i=1; start+i <= (start+end)/2; i++)
        reverse_str(str, start+i, end - i);
}
