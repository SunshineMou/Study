/*!
 * \file	stack_ADT.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-10 14:09:08
 */
#include <stdlib.h>
#include <stdio.h>
#include "stack_ADT.h"

static data sequence;
static data max_sequence;
static data *stack;

int stack_init(data num)
{
    max_sequence = num;
    if((stack = malloc(num * sizeof *stack)) == NULL)
        return 0;
    sequence = 0;
    return 1;
}

void stack_push(data num)
{
    if(stack_full(num)){
        printf("Push error!\n");
        exit(0);
    }
    stack[sequence++] = num;
}

data stack_pop()
{
    if(stack_empty()){
        printf("Push error!\n");
        exit(0);
    }
    return stack[--sequence];
}

int stack_empty()
{
    if(sequence == 0){
        printf("The stack is empty!\n");
        return 1;
    }
    return 0;
}

int stack_full()
{
    if(sequence == max_sequence){
        printf("The stack is full!\n");
        return 1;
    }
    return 0;
}

void stack_release()
{
    free(stack);
    printf("The memery release success!\n");
}

static char *char_stack;
static unsigned int char_sequence;
static unsigned int char_max_sequence;

int char_stack_init(char num)
{
    char_max_sequence = num;
    if((char_stack = malloc(num * sizeof *char_stack)) == NULL)
        return 0;
    char_sequence = 0;
    printf("The init size of the stack is: %d\n", char_max_sequence);
    return 1;
}

void char_stack_push(char num)
{
    if(char_stack_full(num)){
        printf("Push error!\n");
        exit(0);
    }
    char_stack[char_sequence++] = num;
}

char char_stack_pop()
{
    if(char_stack_empty()){
        printf("Push error!\n");
        exit(0);
    }
    return char_stack[--char_sequence];
}

int char_stack_empty()
{
    if(char_sequence == 0){
        printf("The stack is empty!\n");
        return 1;
    }
    return 0;
}

int char_stack_full()
{
    if(char_sequence == char_max_sequence){
        printf("The stack is full!\n");
        return 1;
    }
    return 0;
}

void char_stack_release()
{
    free(char_stack);
    printf("The memery release success!\n");
}
