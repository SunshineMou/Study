/*!
 * \file	signal_raise.c
 * \brief	
 * \author	SunshineMou
 * contact  qingtianmou@gmail.com
 * \version	0.00
 * \date	12-02-28 14:34:54
 */
#include <stdio.h>
#include <signal.h>

typedef void sig_handle(int);
void signal_sigint_handler(int signo);

/*!
 * \brief raise -->向进程本身发送指定的信号
 *
 * \param argc
 * \param argv[]
 *
 * \return 
 */
int main(int argc, char* argv[])
{
    if(signal(SIGINT, signal_sigint_handler) == SIG_ERR){
        printf("Register the signal handler for the SIGINT error!\n");
        return 0;
    }
    sleep(1);
    raise(SIGINT);

    sleep(2);
    printf("Done ...\n");
     
    return 0;
}

void signal_sigint_handler(int signo){
    printf("In the signal handler!\n");
}

