/*!
 * \file	grep.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-15 19:01:25
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <func_xiaodong.h>

int search_ignore_case(const char *source,char *pattern);
int search_normal(const char *source,char *pattern);
int search(const char * source,char *pattern,char option,char choice);
int search_file(const char *source,char *pattern,char option);
int process_option(int argc,char *argv[]);
int read_file(const char *source, char *pattern, char option);
int search_directory(const char *source,char *pattern,char option);
//extern int strstr_nocase(const char *source, char *pattern);
/*!
 * \brief Process parameter;
 */
struct parameter
{
    char  version;          //Display the version information signal;
    char  help_info;        //Display the help information signal;
    char  pattern;          //
    char  file;             //
    char  option;           //
    char  usage;
    char  directory;        //
    char *pattern_info[10];     //
    char *file_info[10];      //
    char *directory_info[10];   //    
}param;

/*!
 * \brief This arry is used to display the version information;
 */
static char version[]="\n"
"    Author: sunshine      version:0.0.1\n"
"    function: grep                     \n"
"                                       \n"
;
                
/*!
 * \brief This arry is used to display the usage;
 */
static char usgmsg[] = 
"Usage: ./grep [OPTIONS] [-e PATTERN | -f FILE] [FILE...]\n"
"To get more information, please issue ./grep -h\n"
;

/*!
 * \brief This arry is used to display the help information;
 */
static char help[]=
"        \n"
"    Uasge: grep [options] parameter directory\n"
"    The 'grep' function is used to search the files which contain the 'parameter' in its' name;\n"
"        \n"
"    Options and its meaning:\n"
"        -i, --ignore-case    The search function will ignore case;\n"
"        -s, --sensitive      The pattern could be the anywhere of the search file's name, but case sensitive ;\n"
"        -f, --file           Search the 'pattern' in the file ;\n"
"        \n"
"    Miscellaneous:\n"
"        -h                   display help information and exit;\n"
"        -u,                  display the usage;\n"
"        -v                   display the version information and exit;\n"
"        \n"
;
/*!
 * \brief This is the main function;
 *
 * \param argc
 * \param argv[]
 *
 * \return 
 */
int main(int argc, char* argv[])
{
    int i,j;
    /*
     * Use the function 'getopt' to receive the parameter;
     */
    process_option(argc, argv);
    /*
     * Display the help information;
     */
    if(param.help_info=='h')
    {
        fputs(help,stdout);
        exit(0);
    }
    /*
     * Search the 'pattern' in the file;
     */
    if(param.version=='v')
    {
        fputs(version,stdout);
        exit(0);
    }
    if (param.usage=='u') 
    {  
        fputs(usgmsg, stderr); 
        exit(-1); 
    }
    /*
     * Search the 'pattern' in the directory;
     */
    if(param.directory=='d')
    {
        for(i=0;param.directory_info[i]!=NULL;i++)
        {
            if(strcmp(param.directory_info[0],"-")==0)
                exit(-1);
            DIR *dp;
            struct dirent *dirp;
            if((dp=opendir(param.directory_info[i]))==NULL)
                printf("Can not open %s\n",argv[1]);
            while((dirp=readdir(dp))!=NULL)
            {
                for(j=0;param.pattern_info[j]!=NULL;j++)
                {
                    if(search(dirp->d_name,param.pattern_info[j],param.option,param.directory)!=0)
                        printf("%s\n",dirp->d_name);
                }
            }
            closedir(dp);
        }
    }
    /*
     * search the pattern in the file;
     */ 
    if(param.file=='f')
    {
        for(i=0;param.file_info[i]!=NULL;i++)
        { 
            if(strcmp(param.file_info[0],"-")==0)
                exit(-1);
            for(j=0;param.pattern_info[j]!=NULL;j++)
                if(search(param.file_info[i],param.pattern_info[j],param.option,param.file)!=0)
                    printf("-----------------------------------------This is what we find;\n");
        }
    }
    exit(0);
}
/*!
 * \brief Process the option information;
 *
 * \param argc
 * \param argv[]
 *
 * \return 
 */
int process_option(int argc,char *argv[])
{
    int ch;
    opterr=0;
    int patternindex=0;
    int fileindex=0;
    int dirindex=0;
    FILE *pattern_stream;
    while((ch=getopt(argc,argv,"usihve:f:d:"))!=-1)
    {
        switch(ch)
        {
        case 'i':
            param.option = 'i';
            break;
        case 'e':
            param.pattern = 'e';
            param.pattern_info[patternindex++]=optarg;
            break;
        case 'h':
            param.help_info='h';
            break;
        case 'd':
            param.directory='d';
            param.directory_info[dirindex++]=optarg;
            break;
        case 's':
            param.option='s';
            break;
        case 'v':
            param.version='v';
            break;
        case 'u':
            param.usage='u';
            break;
        case 'f':
            param.file = 'f';
            param.file_info[fileindex++]=optarg;
            break;
        case '?':
            if (optopt == 'e' || optopt == 'f') 
            {
                fprintf(stderr, "Option -%c require argument\n", optopt);
                exit(-1);
            } 
            else if (isprint(optopt)) 
            {
                fprintf(stderr, "Option -%c: unkown option\n", optopt);
                exit(-1);
            } 
            else 
            {
                fprintf(stderr, "Unkown option\n");
                exit(-1);
            }
            break;
        default:
            printf("other option:%c\n",ch);  
            break;
        }    
    }
    while (optind < argc) 
    {   
        if (param.pattern_info[0] == NULL) 
        { 
            param.pattern_info[patternindex++] = argv[optind++];
        }
        if(param.file=='f')
            param.file_info[fileindex++] = argv[optind++]; 
        if(param.directory=='d')
            param.directory_info[dirindex++] = argv[optind++];   
    }
    if (param.file_info[0] == NULL )
    { 
        param.file_info[0] = "-";
    }
    if (param.directory_info[0]==NULL )
    { 
        param.directory_info[0] = "-";
    }
    return 0;
}

/*!
 * \brief This function begins the search process;
 *
 * \param source
 * \param pattern
 * \param option
 * \param choice
 *
 * \return 
 */
int search(const char * source, char *pattern, char option, char choice)
{
    int goal=0;
    if(choice=='d')
    {
        switch(option)
        {
            case 'i':
                goal=search_directory(source, pattern, 'i');
                break;
            case 's':
                goal=search_directory(source, pattern, 's');
                break;
            default:
                goal=search_directory(source, pattern, 'i');
                break;
        }
    }
    if(choice=='f')
    { 
        switch(option)
        {
            case 'i':
                goal=search_file(source,pattern,'i');
                break;
            case 's':
                goal=search_file(source,pattern,'s');
                break;
            default:
                goal=search_file(source,pattern,'s');
                break;
        }
    }
    if(goal==0)
        return 0;
    return 1;
}

int search_directory(const char *source,char *pattern,char option)
{
    int goal;
    if(option == 'i')
        goal=strstr_nocase(source,pattern);
    if(option == 's')
        goal=search_normal(source,pattern);
    return goal;
}
/*!
 * \brief This function is used to define the search way---->Ignore case;
 *
 * \param source
 * \param pattern
 *
 * \return 
 */
int search_ignore_case(const char *source,char *pattern)
{
    int i=0;
    for(;*source!='\0';source++)
    {
        for(;(*(pattern+i)==*(source+i) || *(pattern+i)==(*(source+i)+0x20)) && *pattern!='\0';i++)
        {
            if(*(pattern+i+1)=='\0')
            return 1; 
        }
        i=0;
    }
    return 0; 
}

/*!
 * \brief This function is used to define the search way---->Case sensitive
 *
 * \param source
 * \param pattern
 *
 * \return 
 */
int search_normal(const char *source,char *pattern)
{ 
    int i=0;
    for(;*source!='\0';source++)
    {
        for(;*(pattern+i)==*(source+i) && *pattern!='\0';i++)
        {
            if(*(pattern+i+1)=='\0')
            return 1; 
        }
        i=0;
    }
    return 0; 
}

/*!
 * \brief This function is used to search pattern in a file;
 *
 * \param source
 * \param pattern
 * \param option
 *
 * \return 
 */
int search_file(const char *source, char *pattern, char option)
{
    struct stat buf;
    if(lstat(source, &buf)<0)
    {
        printf("lstat error\n");
        return 0;
    }
    if(S_ISREG(buf.st_mode))
    {
        if(read_file(source, pattern, option))
            return 1;
    }   
   return 0; 
}

/*!
 * \brief    This function is used to read file in different way;
 *
 * \param source
 * \param pattern
 * \param option
 *
 * \return 
 */
int read_file(const char *source, char *pattern, char option)
{
    int i = 0;
    int result = 0;
    FILE *fd;
    char buf[1101];
    fd=fopen(source,"r");
    while(fgets(buf,1101,fd)!=NULL)
    {
        i++;
        if(option == 's')
        {
            if(search_normal(buf,pattern))
            {
                result = 1;
                printf("  %s:The %d line contain the '%s'\n",source,i,pattern);
                printf("  %s\n",buf);
            }
        }
        if(option == 'i')
        { 
            if(strstr_nocase(buf,pattern))
            {
                result = 1;
                printf("  %s:The %d line contain the '%s'\n",source,i,pattern);
                printf("  %s\n",buf);
            }
        }
    }

    if(result == 0)
        return 0;
    return 1;
}
