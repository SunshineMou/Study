/*!
 * \file	signal_fork.c
 * \brief   sigqueue --> 传递的信号可以附加信息	
 * \author	SunshineMou
 * contact  qingtianmou@gmail.com
 * \version	0.00
 * \date	12-02-28 15:12:56
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*void sig_func(int signo);*/
void sig_func(int signo, siginfo_t *info, void *contest);

#define SYS_ERROR  -1
#define SYS_SUCCESS 1

pid_t parent;
pid_t child;

int main(int argc, char* argv[])
{
    int status;
    pid_t  pid;
    sigval_t sigval = {1};
    parent = getpid();

    if((pid = fork()) == -1){
        printf("Fork child error!\n");
        return SYS_ERROR;
    }
    /*==========================child===========================*/
    else if(pid == 0){
        child = getpid();    
        printf("The pid of the child is: %ld\n", (long int)child);
        struct sigaction old_action, new_action;
        new_action.sa_handler = sig_func;
        new_action.sa_flags   = 0 | SA_SIGINFO; /*控制信号附加参数的有效与否*/
        sigemptyset(&new_action.sa_mask);

        if(sigaction(SIGINT, &new_action, &old_action) < 0){
            printf("Add signal action error!\n");
            return SYS_ERROR;
        }
        /*if(signal(SIGINT, sig_func) == SIG_ERR){*/
            /*printf("Add signal action error!\n");*/
            /*return SYS_ERROR; */
        /*}*/
        printf("Add signal action successful!\n");
        pause();
        return 0;
    }
    /*=======================parent============================*/
    sleep(2);
    printf("The pid of the parents is: %ld\n", (long int)parent);
    if(sigqueue(pid, SIGINT, sigval) != 0){
        printf("Send signal to the child error ...\n");
        return SYS_ERROR;
    }
    printf("Send signal to the child success ...\n");
    waitpid(child, &status, 0);

    if(!WIFEXITED(status))
        printf("Child is terminated by SIGUSR1 unnormally ...\n");
    else
        printf("Child is terminated by SIGUSR1 normally ...  \n");
     
    return 0;
}

/*!
 * \brief 带有附加信息的信号处理函数
 *
 * \param signo
 * \param info
 * \param contest
 */
void sig_func(int signo, siginfo_t *info, void *contest){
    printf("In the SIGUSR1 signal action process ...\n");
    printf("The attached info of the signal:%d ...\n", info->si_value.sival_int);
}

