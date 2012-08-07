/*!
 * \file	dpopen_test.c
 * \brief	
 * \author	SunshineMou
 * contact  qingtianmou@gmail.com
 * \version	0.00
 * \date	12-02-21 14:46:22
 */
#include <stdio.h>
#include <stdlib.h>
#include "dpopen.h"
#define MAXLINE 80

int main()
{
    char    line[MAXLINE];
    FILE    *fp;
    fp = dpopen("sort");
    if (fp == NULL) {
        perror("dpopen error");
        exit(1);
    }
    fprintf(fp, "orange\n");
    fprintf(fp, "apple\n");
    fprintf(fp, "pear\n");
    if (dphalfclose(fp) < 0) {
        perror("dphalfclose error");
        exit(1);
    }
    for (;;) {
        if (fgets(line, MAXLINE, fp) == NULL)
            break;
        fputs(line, stdout);
    }
    dpclose(fp);
    return 0;
}

