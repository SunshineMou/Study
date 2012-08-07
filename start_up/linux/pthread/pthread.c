/*!
 * \file	pthread.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-06 10:28:13
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

struct example{
    char              test[10];
    pthread_rwlock_t  e_lock;
};

void cleanup_1(void *arg){
    printf("The cleanup func_1!\n");
}

void cleanup_2(void *arg){
    printf("The cleanup func_2!\n");
}

void cleanup_3(void *arg){
    printf("The cleanup func_3!\n");
    free(arg);
}

void *func_first(void *arg){
    fprintf(stderr, "Pthread_1\n");
    pthread_cleanup_push(cleanup_2, NULL);

    struct example *example = arg;
    pthread_rwlock_wrlock(&example->e_lock);
    fprintf(stderr, "The string which saw by pthread_1 is:%s\n", example->test);
    example->test[0] = 's';
    fprintf(stderr, "The pthread 1 change the string into:%s\n", example->test);
    pthread_rwlock_unlock(&example->e_lock);

    pthread_cleanup_pop(1);
    pthread_exit((void *)0);
}

void *func_second(void *arg){
    fprintf(stderr, "Pthread_2\n");
    pthread_cleanup_push(cleanup_1, NULL);

    struct example *example = arg;
    int i = 0;
    for(; i < 10; i++){
        pthread_rwlock_rdlock(&example->e_lock);
        fprintf(stderr, "The string which saw by pthread_2 is:%s\n",  \
                example->test);
        pthread_rwlock_unlock(&example->e_lock);
        sleep(1);
    }

    pthread_cleanup_pop(1);
    pthread_exit((void *)0);
}

int example_init(void **arg){
    struct example *example;
    example = malloc(sizeof(struct example));
    if(example  == NULL){
        fprintf(stderr, "Malloc memory error!\n");
        return 0;
    }
    if(pthread_rwlock_init(&example->e_lock, NULL) != 0){
        fprintf(stderr, "Init rwlock error!\n");
        return 0;
    }
    strncpy(example->test, "xiaodong", 9);
    *arg = (void *)example;
    printf("The initial string is:%s\n", ((struct example *)*arg)->test);
    
    return 1;
}

int main(int argc, char* argv[])
{
    pthread_t first_tid;
    pthread_t second_tid;
    void *example;
    void *p_exit;

    if(!example_init(&example))
        return 0;

    pthread_cleanup_push(cleanup_3, example);

    if(pthread_create(&first_tid, NULL, func_first, example) != 0){
        fprintf(stderr, "%s\n", "Create pthread first error!");
        return 0;
    }
    /*pthread_detach(first_tid);*/

    if(pthread_create(&second_tid, NULL, func_second, example) != 0){
        fprintf(stderr, "%s\n", "Create pthread second error!");
        return 0;
    }
    /*pthread_detach(second_tid);*/
    
    pthread_join(first_tid, &p_exit);
    printf("Pthread_1 exit code:%d\n", (int)p_exit); 
    pthread_join(second_tid, &p_exit);
    printf("Pthread_2 exit code:%d\n", (int)p_exit); 
    pthread_cleanup_pop(1);
    return 0;
}

