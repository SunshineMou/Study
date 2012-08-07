/*!
 * \file	getpwnam_signal.c
 * \brief	
 * \author	SunshineMou
 * contact  qingtianmou@gmail.com
 * \version	0.00
 * \date	12-02-15 16:27:52
 */
#include <stdio.h>
#include <pwd.h>
#include "apue.h"

int print_user_info(void);
static void my_alarm(int signo);

int main(void)
{
    struct passwd   *ptr;

    signal(SIGALRM, my_alarm);
    alarm(1);
    for ( ; ; ) {
        if ((ptr = getpwnam("sunshine")) == NULL)
            err_sys("getpwnam error");
        if (strcmp(ptr->pw_name, "sar") != 0)
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
    }
}

static void my_alarm(int signo)
{
    struct passwd   *rootptr;

    printf("in signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL)
        err_sys("getpwnam(root) error");
    alarm(1);
}

int print_user_info(void)
{
    struct passwd * pw;
    char *username = "sunshine";
    pw = getpwnam(username);
    if (!pw) {
        printf("%s is not exist\n", username);
        return -1;
    }

    printf("pw->pw_name   = %s\n", pw->pw_name);
    printf("pw->pw_passwd = %s\n", pw->pw_passwd);
    printf("pw->pw_uid    = %d\n", pw->pw_uid);
    printf("pw->pw_gid    = %d\n", pw->pw_gid);
    printf("pw->pw_gecos  = %s\n", pw->pw_gecos);
    printf("pw->pw_dir    = %s\n", pw->pw_dir);
    printf("pw->pw_shell  = %s\n", pw->pw_shell);
}
