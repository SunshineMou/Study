/*!
 * \file	stream.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-11 08:49:51
 */

#include <aupe.h>

static void sig_pipe(int);   /* our signal handler */

int main(int argc, char* argv[])
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	line[MAXLINE];
    
    /*SIGPIPE：在写一个读端已被关闭的管道时产生此信号*/
	if (signal(SIGPIPE, sig_pipe) == SIG_ERR)   /*注册信号处理函数*/
		err_sys("signal error");

	if (s_pipe(fd) < 0)			/* need only a single stream pipe */
		err_sys("pipe error");

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} 
    /*父进程*/
    else if (pid > 0) {							/* parent */
		close(fd[1]);
		while (fgets(line, MAXLINE, stdin) != NULL) {
			n = strlen(line);
			if (write(fd[0], line, n) != n)
				err_sys("write error to pipe");
			if ((n = read(fd[0], line, MAXLINE)) < 0)
				err_sys("read error from pipe");
			if (n == 0) {
				err_msg("child closed pipe");
				break;
			}
			line[n] = 0;	/* null terminate */
			if (fputs(line, stdout) == EOF)
				err_sys("fputs error");
		}

		if (ferror(stdin))
			err_sys("fgets error on stdin");
		exit(0);
	} 
    /*子进程*/
    else {									/* child */
		close(fd[0]);
		if (fd[1] != STDIN_FILENO && dup2(fd[1], STDIN_FILENO) != STDIN_FILENO)
			err_sys("dup2 error to stdin");
		if (fd[1] != STDOUT_FILENO && dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
			err_sys("dup2 error to stdout");
		if (execl("./add2", "add2", (char *)0) < 0)
			err_sys("execl error");
	}
	exit(0);
}


static void sig_pipe(int signo){
	printf("SIGPIPE caught\n");
	exit(1);
}

