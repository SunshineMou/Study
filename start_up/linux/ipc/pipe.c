/*!
 * \file	pipe.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-12 17:12:27
 */
#include "apue.h"

int main(void)
{
    int     n;
    int     fd[2];
    pid_t   pid;
    char    line[MAXLINE];

    if (pipe(fd) < 0)
        err_sys("pipe error");
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {       /* parent */
        sleep(1);

        long max = 0;
        max = fpathconf(fd[1], _PC_PIPE_BUF);
        printf("The buf of the pipe is: %ld\n", max);

        int val_parent = 1;
        printf("Tha address of val_parent is: %p\n", &val_parent);
        close(fd[0]);
        sleep(5);
        write(fd[1], "hello world\n", 12);
    } else {                /* child */
        int val_children = 1;
        printf("Tha address of val_children is: %p\n", &val_children);
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        printf("Read data from parent!\n");
        write(STDOUT_FILENO, line, n);
    }

    sleep(1);
    exit(0);
}
