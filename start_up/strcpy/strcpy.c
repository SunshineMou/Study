#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
char *r_strcpy(char *destination, char *source);
char *r_strncpy(char *destination, const char *source, size_t num);

int
main(int arg,char *argv[])
{
    if(arg!=3)
        {
            printf("Usage:strcpy.out <destination> <source>\n");
            return -1;
        }
    printf("The destination string is: %s\n",argv[1]);
    printf("The source string is: %s\n",argv[2]);
    clock_t start,end;
    int i;
    start=clock();
/*
    for(i=0;i<1000000;i++)
        strcpy(argv[1],argv[2]);
    end=clock();
*/
    for(i=0;i<1000000;i++)
        r_strcpy(argv[1],argv[2]); 
    end=clock();

    printf("The time was:%f\n ",(double)(end-start)/CLOCKS_PER_SEC);

/*
    if(strcpy(argv[1],argv[2])==NULL)
    {
	printf("Error\n");
	return -1;
    }
    printf("After the function 'strcpy',the destination string is: %s\n",argv[1]);
*/
/*
    if(strncpy(argv[1],argv[2],3)==NULL)
        {
            printf("Error\n");
            return -1;
        }
    printf("After the function 'strncpy',the destination string is: %s\n",argv[1]);
*/
    return 1;
}

/*Rewrite function strcpy(char *destination, char *source) to copy the C string pointed by 
source into the array pointed by destination, including the terminating null character.*/

char *r_strcpy(char *destination, char *source)
{
/*
    *The following code is to detect if the destination is enough to store
    the source string***************************************************
    int des_len=0;
    int src_len=0;
    while(*(destination+des_len)!=0x00)
	des_len++;
    while(*(source+src_len)!=0x00)
	src_len++;
    if(des_len<src_len)
    {
	printf("The destination is not long enough to store the source\n");
	return NULL;
    }
*/
    /*****The main function code*****/
    int i=0;
    while(*(source+i)!=0x00)
    {
	*(destination+i)=*(source+i);
	    i++;	
    }
    *(destination+i)=0x00;
    return destination;
}
/*Rewrite function strncpy(char *destination, const char *source, size_t num)*/

char *r_strncpy(char *destination, const char *source, size_t num)
{
    /*The following code is to detect if the destination is enough to store
    the source string***************************************************/
    int des_len=0;
    while(*(destination+des_len)!=0x00)
	des_len++;
    if(des_len<num)
    {
	printf("The destination is not long enough to store the source\n");
	return NULL;
    }
    /********The main function code********/
    int i=0;
    int j=0;
    for(i=0;i<num;i++)
    {
	*(destination+i)=*(source+i);
	if(*(source+i)==0x00)
        {
	    for(j=i;j<num;j++)
	        *(destination+j)=0x00;	
	    break;
	}
    }
    return destination;
}

