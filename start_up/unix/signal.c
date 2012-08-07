/*!
 * \file	signal.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-12 10:29:22
 */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void new_op(int, siginfo_t *, void *);

int main(int argc, char* argv[])
{
    struct sigaction  act;
    int    sig;
    pid_t  pid;

    pid = getpid();
    sig = atoi(argv[1]);

    sigemptyset(&act.sa_mask);
    act.sa_sigaction = new_op;
    act.sa_flags     = SA_SIGINFO;
    if(sigaction(sig, &act, NULL) < 0) {
        printf("Install signal error\n");
    }
    while(1){
        sleep(2);
        printf("Wait for the signal \n");
    } 
    exit(0);
}

void new_op(int signum, siginfo_t *info, void *myact){
    printf("The int value is %d \n", info->si_int);
}

