/*!
 * \file	holy.c
 * \brief	holy's implementation of Linux's utity---grep
 * 
 * Temporarily not support long option or colored output.
 *
 * \author	LiJunjie
 * contact  holysoros@gmail.com
 * \version	0.01
 * \date	11-03-16 14:49:20
 */

/*
 *程序大致分为两部分：
 *一.分析处理命令行，获取pattern与file，保存到各自数组中；函数名为：process_commandline();
 *二.在每个file中的每一行中查找每个pattern。
 **************************************************
 *第一部分：
 *1.处理每一个option；
 *2.若还有未处理的命令行参数；
 *    1).若命令行参数总数为1~3，则特殊处理;
 *    2).否则，未处理的命令行参数认为是file
 *3.如果没有指定任何file，则添加"-"；
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <unistd.h>

#define MAX_FILE    100 //给定的file的最大数目，暂时这样设计，有缺陷
#define MAX_PATTERN 20  //给定的pattern的最大数目
static char *files[MAX_FILE];   //存放命令行给定的file
static char *patterns[MAX_PATTERN]; //存放命令行给定的pattern

#define MAX_LINE    65535   //一行能包含的最大字符数
static char line[MAX_LINE]; 

static char helpmsg[] = 
"SYNOPSIS\n"
"       grep [OPTIONS] PATTERN [FILE...]\n"
"       grep [OPTIONS] [-e PATTERN | -f FILE] [FILE...]\n"
"\n"
"DESCRIPTION\n"
"       grep  searches  the  named  input  FILEs (or standard input if no files are named, or if a single hyphen-minus (-) is \n"
"       given as file name) for lines containing a match to the given PATTERN.  By default, grep prints the matching lines.\n"
"OPTIONS\n"
"   Generic Program Information\n"
"       --help Print a usage message briefly summarizing these command-line options and the bug-reporting address, then exit.\n"
"\n"
"       -V, --version\n"
"              Print the version number of grep to the standard output stream.  This version number should be included in all \n"
"              bug reports (see below).\n"
"   Matching Control\n"
"       -e PATTERN, --regexp=PATTERN\n"
"              Use PATTERN as the pattern.  This can be used to specify multiple search patterns, or to protect a pattern beginning \n"
"              with a hyphen (-).  (-e is specified by POSIX.)\n"
"\n"
"       -f FILE, --file=FILE\n"
"              Obtain patterns from FILE, one per line.  The empty file contains zero patterns, and therefore matches nothing.  \n"
"              (-f is specified by POSIX.)\n"
;

static char usgmsg[] = 
"Usage: ./holy [OPTIONS] [-e PATTERN | -f FILE] [FILE...]\n"
"To get more information, please issue ./holy -h\n"
;
char *srhstr(char *, char *);
int colored_msg(int, char *, char *);

#define VERSION "0.01.00"
#define VERSION_MSG "Holy grep "VERSION

/*
 *第二部分：
 *1.还有未处理的file
 *    1).打开该file
 *    2).如果打开失败，则输出错误信息，退出；
 *    3).否则，读取该文件
 *        a.该文件还有未处理的行
 *            a).在该行中搜索每一个pattern
 *            b).若搜索到，则输出相关信息；
 *            c).否则，返回a
 *        b.返回1.
 */
int main(int argc, char* argv[])
{
    int process_commandline(int, char *[]);
    process_commandline(argc, argv);

    int i, flags = 0;
    if (files[1] != NULL)   //如果多于一个文件，则输出文件名信息
        flags = 1;
    for (i = 0; files[i] != NULL; i++) {  //还有未处理的file
        FILE *stream;
        if (strcmp(files[i], "-") == 0) {   //从stdin获取数据
            stream = stdin;
        } else {
            stream = fopen(files[i], "r");    //打开该file
        }
        if (stream == NULL) {   //该文件打开失败，输出错误信息，退出
            fprintf(stderr, "%s: cann't open the file.\n", files[i]);
            exit(-1);
        }
        while (fgets(line, MAX_LINE, stream) != NULL) {   //读取该文件，还有未处理的行
            int j;
            for (j = 0; patterns[j] != NULL; j++) { //在该行中，搜索每一个pattern
                char *occur = NULL;
                if ((occur = srhstr(line, patterns[j])) != NULL) {   //在该行中搜索到了某个pattern
                    colored_msg(flags, files[i], line);   //输出相关信息
                }
            }
        }
    }

    return 0;
}

/*!
 * \brief proccess command line;temporarily, donn't support long option.
 *
 * \param argc
 * \param argv[]
 *
 * \return 
 */
/*
 *第一部分：
 *1.处理每一个option；
 *2.若还有未处理的命令行参数；(argv已被排序)
 *    1).若数组patterns还为空
 *        a.则将argv[optind]赋予patterns；
 *    2).否则，未处理的命令行参数认为是file
 *3.如果patterns为空，则输出usage信息,并退出；
 *4.如果files为空，则添加"-"；
 */
int process_commandline(int argc, char *argv[])
{
    int fileindex = 0;
    int patternindex = 0;
    //以下代码段处理没有OPTION的情况
   
    //处理每一个option
    FILE *pattern_stream;   //case中不能定义变量
    opterr = 0;     //disable output error mesage by getopt function
    char c;
    while ((c = getopt(argc, argv, "hVe:f:")) != -1) {
        switch (c) {
            case 'h':   //打印help信息
                fputs(helpmsg, stdout);
                break;
            case 'V':   //打印version信息
                printf("%s\n", VERSION_MSG);
                break;
            case 'e':   //指定pattern
                patterns[patternindex++] = optarg;
                break;
            case 'f':   //指定pattern从这个file中获取
                pattern_stream = fopen(optarg, "r");
                if (pattern_stream == NULL) {
                    printf("%s: cann't open pattern file.\n", optarg);
                    exit(-1);
                }
                while (fgets(line, MAX_LINE, pattern_stream) != NULL) {
                    patterns[patternindex++] = line;
                }
                break;
            case '?':
                if (optopt == 'e' || optopt == 'f') {
                    fprintf(stderr, "Option -%c require argument\n", optopt);
                    exit(-1);
                } else if (isprint(optopt)) {
                    fprintf(stderr, "Option -%c: unkown option\n", optopt);
                    exit(-1);
                } else {
                    fprintf(stderr, "Unkown option\n");
                    exit(-1);
                }
                break;
            default:
                break;
        }
    }
    while (optind < argc) {    //还有未处理的命令行参数
        if (patterns[0] == NULL) {  //如果patterns还为空，则将当前optind指向的参数赋予patterns
            patterns[patternindex++] = argv[optind++];
        }
        files[fileindex++] = argv[optind++];    //否则，未处理的命令行参数认为是file
    }
    if (patterns[0] == NULL) {  //如果patterns还为空，则输出错误信息，退出
        fputs(usgmsg, stderr); 
        exit(-1); 
    }
    if (files[0] == NULL) { //如果files为空，则从stdin获取数据
        files[0] = "-";
    }

    return 0;
}

/*!
 * \brief temporarily use strstr; Should be modified if support regular expression.
 *
 * \param s
 * \param t
 *
 * \return 
 */
char *srhstr(char *s, char *t)
{
    return strstr(s, t);
}

/*!
 * \brief 输出查找成功信息，只有一个文件时，不输出文件名；有多个文件时，前缀文件名.
 *
 * \param flags 为1时，输出文件名；为0时，不输出文件名.
 * \param fn
 * \param line
 *
 * \return 
 */
int colored_msg(int flags, char *fn, char *line)
{
    if (flags & 0x01) {
        return printf("%s: %s", fn, line);
    } else {
        return printf("%s", line);
    }
}
