/*!
 * \file	deap_stack_2.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-04 10:55:18
 */
#include <stdio.h>
#include <malloc.h>

typedef struct node   
{   
    int   value;   
    struct   node   *next;   
}NODE; 

NODE   *top,*s,*bottom ;

void empty()   
{        
    top = NULL;   
}

/*!
 * \brief 执行压栈操作
 *
 * \param element_value
 */
void push(int   element_value)   
{   
    s=(NODE*)malloc(sizeof(NODE));   
    s->value=element_value;   
    s->next=top;   
    if(top==NULL)   
    {   
        bottom=s;   
    } 

    top=s;  
}

/*!
 * \brief 执行出栈操作
 */
void pop()   
{   
    int   y;  
    if(top==NULL)   
    {   
        printf("stack is empty\n");   
        return;
    }   

    s=top;   
    y=top->value;   
    top=top->next;   
    free(s);      /*===出栈-->释放内存===*/ 
    printf("pop element value is %d\n",y);   
}

void main()   
{   
    int   b,n,i;

    empty();      /* 1.建立一个空的堆栈 */
    printf("How   many   times   do   you   want   to   push   and   to   pop?\n");   
    scanf("%d",&n);   
    for(i=1;i<=n;i++)   
    {   
        printf("Enter   the   %d   time's  push value:",i);   
        scanf("%d",&b);   
        push(b);  /* 2.执行压栈操作 */ 
    }   
    printf("\nThe   value   of   bottom=%d\n",bottom->value);   

    for(i=1;i<=n;i++)   
    {   
        pop();   /* 3.执行出栈操作 */ 
    }

    pop() ;
}   
