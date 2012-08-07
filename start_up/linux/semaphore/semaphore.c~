/*!
 * \file	semaphore.c
 * \brief	
 * \author	SunshineMou
 * contact  qingtianmou@gmail.com
 * \version	0.00
 * \date	12-02-29 09:42:23
 */
#include <linux/sem.h>
#include <stdio.h>
#include <errno.h>

#define SEM_PATH    "my_sem"
#define max_tries   3 
#define SYS_ERROR  -1
#define SYS_SUCCESS 1
int semid;

int main(int argc, char* argv[])
{
    int    flag1, flag2, key, i, init_ok, tmperrno;
    /*
     * 内核为每个信号量都设置了一个semid_ds结构：
     */
    struct semid_ds sem_info;
    /*
     * seminfo:
     *   此结构体对应的数据是针对semctl中IPC_INFO命令
     *   所要获取的数据结构-->主要包括系统对信号量的一
     *   般的设置信息。
     */
    struct seminfo  sem_info2; 
    /*
     *semun:
     *   针对semctl其余多个特种命令的参数的集合
     *   union semun {
     *      int val;                //for SETVAL
     *      sturct semid_ds *buf;   //for IPC_STST and IPC_SET
     *      unsigned short  *array; //for GETALL and SETALL 
     *   }
     */
    union  semun    arg;  
    /*
     * sembuf:
     *   指向一个信号量操作数组
     */
    struct sembuf   askfor_res, free_res;
    flag1 = IPC_CREAT | IPC_EXCL | 00666;
    flag2 = IPC_CREAT | 00666;

    if((key = ftok(SEM_PATH, 'a')) == -1){
        perror("Creat key error ...");
        return SYS_ERROR;
    } 

    init_ok = 0;
    semid = semget(key, 1, flag1);
    
    /*
     * 与此key值对应的信号量已经存在
     *
     * 此时就存在一个解决竞争的问题：
     * 
     * 因为发生此情况的原因有可能是：
     *     一个进程正在创建信号量，并处在初始化的阶段；
     *     此时，当前进程或另一个进程调用semget来获取
     *     或创建该信号量时就产生了一个竞争的问题。
     *
     * 解决方法：
     *     当进程对信号量进行初始化时，初始完毕之后，
     *     信号量对应的结构体参数中的sem_otime的值会
     *     置为 0 。使另一个进程睡眠等待此参数变为0之
     *     后，在继续对此信号量进行操作。
     */
    if(semid < 0){ 
        tmperrno = errno;
        /*
         * errno: errno在成功的系统函数调用后的值是未定义的；
         *        这个系统函数同样包括perror函数本身；
         */
        perror("semget");
        if(tmperrno == EEXIST){
            semid = semget(key, 1, flag2);
            /*
             * flag2 只包含了IPC_CREAT标志。
             * 参数nsems(这里为1)必须与原来
             * 的信号灯数目一致
             */
            arg.buf = &sem_info;
            for(i = 0; i < max_tries; i++){
                if(semctl(semid, 0, IPC_STAT, arg) == -1){  
                    perror("semctl error"); 
                    i = max_tries;
                }
                else{ 
                    if(arg.buf->sem_otime != 0){ 
                        i = max_tries;  
                        init_ok = 1;
                    }
                    else   
                        sleep(1);  
                }
            }
            /*
             * 对前面创建的信号量的信号量集进行检测，
             * 是否已经设定好相关的参数，如果以设定
             * 好，则跳过下面的初始化阶段；
             */
            if(!init_ok){
                arg.val = 1;
                if(semctl(semid, 0, SETVAL, arg)==-1) 
                    perror("semctl setval error");
            } 
        }
        else{
            perror("semget error, process exit");  
            return SYS_SUCCESS;  
        }
    }
    /*根据此key值创建新的信号量成功，进行下面的初始化*/
    else{
        arg.val=1;
        if(semctl(semid, 0, SETVAL, arg) == -1)
            perror("semctl setval error");
    }
    arg.buf = &sem_info;
    if(semctl(semid, 0, IPC_STAT, arg)==-1)
        perror("semctl IPC STAT");    
    printf("owner's uid is %d\n",     arg.buf->sem_perm.uid);
    printf("owner's gid is %d\n",     arg.buf->sem_perm.gid);
    printf("creater's uid is %d\n",   arg.buf->sem_perm.cuid);
    printf("creater's gid is %d\n",   arg.buf->sem_perm.cgid);

    arg.__buf = &sem_info2;
    if(semctl(semid, 0, IPC_INFO, arg)==-1)
        perror("semctl IPC_INFO");
    printf("the number of entries in semaphore map is %d \n",     arg.__buf->semmap);
    printf("max number of semaphore identifiers is %d \n",        arg.__buf->semmni);
    printf("mas number of semaphores in system is %d \n",         arg.__buf->semmns);
    printf("the number of undo structures system wide is %d \n",  arg.__buf->semmnu);
    printf("max number of semaphores per semid is %d \n",         arg.__buf->semmsl);
    printf("max number of ops per semop call is %d \n",           arg.__buf->semopm);
    printf("max number of undo entries per process is %d \n",     arg.__buf->semume);
    printf("the sizeof of struct sem_undo is %d \n",              arg.__buf->semusz);
    printf("the maximum semaphore value is %d \n",                arg.__buf->semvmx);

    /*请求可用资源*/
    askfor_res.sem_num = 0;
    askfor_res.sem_op  = -1;
    askfor_res.sem_flg = SEM_UNDO;    

    if(semop(semid, &askfor_res, 1)==-1)
        perror("semop error");

    /*在共享资源上做一些处理动作*/
    sleep(3); 
    printf("now free the resource\n");  

    /*释放占用的资源*/
    free_res.sem_num = 0;
    free_res.sem_op  = 1;
    free_res.sem_flg = SEM_UNDO;
    if(semop(semid, &free_res, 1) == -1)
        if(errno==EIDRM)
            printf("the semaphore set was removed\n");

    /*从系统中删除信号量*/
    if(semctl(semid, 0, IPC_RMID) == -1)
        perror("semctl IPC_RMID");
    else 
        printf("remove sem ok\n");

    return 0;
}

