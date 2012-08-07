/*!
 * \file	first_level_FIFO_ADT.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-23 20:04:59
 */
#include <stdio.h>

static int NUM, HEAD, TAIL;

int *queue_init(int maxNum)
{
    int *item;
    item = malloc(maxNum * sizeof(int));
    NUM  = maxNum;
    HEAD = NUM;
    TAIL = 0;
     
    return item;
}

void queue_put(int *queue, int item){
    queue[TAIL++] = item;
    TAIL = TAIL % NUM;
}

int queue_get(int *queue){
    HEAD = HEAD % NUM;
    return queue[HEAD++];
}

int queue_empty(){
    return HEAD % NUM == TAIL;
}

void queue_release(int *queue){
    free(queue);
}
