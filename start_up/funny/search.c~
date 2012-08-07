/*!
 * \file	search.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-04-29 14:13:51
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>

#define LEN sizeof(struct number)
struct number
{
    int num;
    struct number *next;
};

struct number *creat(int amount);
int stoi(char *str);
struct number *search(struct number *point);

int main(int argc, char* argv[])
{
    int result;
    struct number *point;
    struct number *res;
    if(argc != 2)
    {
        printf("Usage:search.out number\n");
        exit(-1);
    }
    result = stoi(argv[1]);
    point = creat(result);
    if((res = search(point)) != NULL)
    {
        printf("The last number after the process is:%d \n",res->num);
    }
    else
    {
        printf("Error!");
    }
    exit(0);
}

/*!
 * \brief This function is used to change the string into integer!
 *
 * \param str
 *
 * \return 
 */
int stoi(char *str)
{
    int i = 0;
    int n = 0;
    for(n= 0 ; isdigit(*(str + i)); i++)
    {
        n = 10 * n + (*(str+i) - 0x30);
    }
    return n;
}

/*!
 * \brief This function is used to build a SQL for the main function;
 *
 * \param amount
 *
 * \return 
 */
struct number *creat(int amount)
{
   struct number *head;
   struct number *p1,*p2;
   int n = 0;
   int i;
   if((p1 = p2 = (struct number *) malloc( LEN )) == NULL)
   {
        printf("Error in malloc the memory!\n");
        exit(-1);
   }
   for(i = 1;i <= amount;i++)
   {
       n = n+1;
       p1->num = i;
       if(n == 1)
           head = p1;
       else
           p2 -> next = p1;
       p2 = p1;
       if((p1 = (struct number *)malloc(LEN)) == NULL)
       {
           printf("Error in malloc the memory!\n");
           exit(-1);
       }
   }
   p2->next = head;
   return head;
}

/*!
 * \brief The follwed function make the 'search' function come true!
 *
 * \param point
 *
 * \return 
 */
struct number *search(struct number *point)
{
    int i = 1;
    struct number *p1;
    struct number *p2;

    p1 = point;
    for(i=1; i<=3; i++)
    {
        if(p1 -> next == p1)
        {
            return p1;
        }
        if( i == 1 )
        {
            p2 = p1;
            p1 = p1 -> next;
        }
        if( i == 2 )
        {
            p2 = p1;
            p1 = p1 -> next;
        }
        if( i == 3 )
        {
            p2->next = p1->next;
            p1 = p2 -> next;
            i = 0;        //注意此时i的值为什么要为0？因为在循环内部进行下一个循环时，for语句要先执行+1操作！
        }
    }    
    return NULL;
}
