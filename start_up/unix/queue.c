/*!
 * \file	queue.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-07-22 14:18:20
 */

#include <stdlib.h>
#include <pthread.h>
#include "apue.h"

struct job {
    struct job  *j_next;
    struct job  *j_prev;
    pthread_t   j_id;         /*Tells which thread handles this jod*/
};

struct queue {
    struct job       *head;
    struct job       *tail;
    pthread_rwlock_t q_lock;
};

int queue_init(struct queue *qp){
    int err;
    qp->q_head = NULL;
    qp->q_tail = NULL;
    err = pthread_rwlock_init(&qp->q_lock,NULL);
    if(err != 0)
        return (err);
    return (0);
}

void job_append(struct queue *qp, struct job *jp){
    pthread_rwlock_lock(&qp->lock);
    jp->next = NULL;
    jp->prev = qp->tail;
    if(qp->q_tail != NULL)
        qp->q_tail->j_next = jp;
    else
        qp->head = jp;
    qp->q_tail = jp;
    pthread_rwlock_unlock(&qp->lock);
}

struct job *job_find(struct queue *qp, pthread_t id){
    struct job *jp;
    if(pthread_rwlock_rdlock(&qp->q_lock) != 0)
        return (NULL);
    for(jp = qp->q_head; jp != NULL; jp = jp->next)
        if(pthread_equal(jp->id, id))
            break;
    pthread_rwlock_unlock(&qp->lock);
    return (jp);
}
int main(int argc, char* argv[])
{
    queue_init(); 
    return 0;
}

