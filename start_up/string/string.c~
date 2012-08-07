#include "stdio.h"
#include <fcntl.h>
#include <string.h>
int strrindex(char *string, char letter);

int
main(int argc,char *argv[])
{  
    char num;
    if(argc !=2)
        {
    	    printf("Uasge:xiaodong.out <string>");
	    return -1;
	}
    printf("The string you just input is:%s,\n",argv[1]);
    printf("Please input the char you want to search:");
    num=getchar();
    printf("The char you want to search is %c\n",num);
    strrindex(argv[1],num);
}
/*!
 * \brief THe function "strrindex" returns the poistion of the rightmost occurrence of the char 'letter' in the string;
 *
 * \param string
 * \param letter
 *
 * \return 
 */
int strrindex(char *string, char letter)
{
    int j=0;
    int search_letter=0;
    for(;*string != '\0'; string++)
	{
        j++;
        if(*string == letter)
		    if(search_letter<=j)
		        search_letter=j;
	}
    if(search_letter==0)
	return -1;
    else
        printf("The location is %d\n",search_letter);
	return search_letter;
}
