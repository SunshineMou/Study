#include "apue.h"

static void	sig_int(int);

int main(void)
{
    sigset_t	newmask, oldmask, waitmask;

    pr_mask("program start: ");

    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal(SIGINT) error");
    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    /*
     * Block SIGINT and save current signal mask.
     */
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_sys("SIG_BLOCK error");

    /*
     * Critical region of code.
     */
    pr_mask("in critical region: ");

    /*
     * Pause, allowing all signals except SIGUSR1.
     */
    if (sigsuspend(&waitmask) != -1)
        err_sys("sigsuspend error");

    pr_mask("after return from sigsuspend: ");

    /*
     * Reset signal mask which unblocks SIGINT.
     */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("SIG_SETMASK error");

    /*
     * And continue processing ...
     */
    pr_mask("program exit: ");

    exit(0);
}

static void sig_int(int signo)
{
    pr_mask("\nin sig_int: ");
}

/*!
 * \brief 打印当前信号屏蔽字所屏蔽的信号
 *
 * \param ptr
 */
void pr_mask(const char* ptr)
{
    sigset_t                sigset;
    int                     errno_save;
    int                     ret;

    errno_save = errno; /*备份errno，防止errno被此程序中的函数更改*/
    ret = sigprocmask(0, NULL, &sigset);
    if(ret == -1){
        perror("sigprocmask error");
        exit(1);
    }
    printf("%s", ptr);

    /*sigismember:测试某个信号是否已加入到信号集中*/
    if(sigismember(&sigset, SIGINT)){
        printf("SIGINT ");
    }

    if(sigismember(&sigset, SIGQUIT)){
        printf("SIGQUIT ");
    }

    if(sigismember(&sigset, SIGUSR1)){
        printf("SIGUSR1 ");
    }

    if(sigismember(&sigset, SIGALRM)){
        printf("SIGALRM ");
    }
    printf("\n");
    errno = errno_save;
}
