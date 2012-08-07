/*!
 * \file	queue.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-25 15:56:55
 */
#include "queue.h"
#include <stdlib.h>

struct pthread_job{
    pthread_t  p_id;
    int        data;
    pthread_id *next;
};
typedef struct pthread_job* queue_job;

struct queue{
    queue_job HEAD;
    queue_job TAIL;
}
typedef struct queue* JOB;

queue_job creat_new(pthread_t id, int sdata, queue_job next)
{
    queue_job new = malloc(sizeof(*new));
    new->p_id = id;
    new->data = sdata;
    new->next = next;
    return new;
}

JOB queue_init(int max_queue_num)
{
    JOB q = malloc(sizeof(*q));
    q->HEAD = NULL;
     
    return q;
}

void queue_put(JOB q, pthread_t id, int data)
{
    if(q->HEAD == NULL){
        q->TAIL = creat_new(id, data, q->HEAD);
        q->HEAD = q->TAIL;
        return;
    }
    q->TAIL->next = creat_new(id, data, q->TAIL->next);
    q->TAIL = q->TAIL->next;
}

int queue_get_data(JOB q)
{
    int data = q->HEAD->data;
    return data;
}

pthread_t queue_get_id(JOB q)
{
    int id = q->HEAD->p_id;
    return id;
}

void job_release(JOB q)
{
    queue_job t = q->HEAD->next;
    free(q->HEAD);
    q->HEAD = t;
}
