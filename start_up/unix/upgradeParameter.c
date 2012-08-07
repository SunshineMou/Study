/*!
 * \file	upgradeParameter.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-18 09:52:32
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <fcntl.h>

#define EXTRACT_PATH "/tmp/etc.tar"

int main(int argc, char* argv[])
{
	int 	dwCntLength;
	char 	*szInputStr;
	char	*pbyTemp;
	FILE 	*fpOutput;
	int  	dwBoundaryCount = 0;
	int 	dwHeaderCount = 0;
	int 	dwLineIndex;
	int		iRet;
	pid_t 	pid;
	int		status;
	struct  rusage rusage;
	int     fd;
	
    printf("Content-Type:text/html\r\n");
    printf("Cache-Control: no-cache\r\n\n");
	dwCntLength = atoi(getenv("CONTENT_LENGTH"));

	if (dwCntLength <= 0) {
		return -1;
	}

    /*为数据收集内存,szInputStr为收集内存的指针*/
	szInputStr = (char *)malloc(dwCntLength+1);

    /*如果收集内存失败*/
    if (szInputStr == NULL) {
        return -1;
    }

    /*将该内存区域清零*/
	memset(szInputStr, 0, dwCntLength);
	szInputStr[dwCntLength] = '\0';
	pbyTemp = szInputStr;
	
    /*从标准输入读取数据，也就是接收用户段上传的数据，将数据读入刚刚所收集的内存中去*/
	fread(szInputStr, dwCntLength, 1, stdin);
	
	while (*(szInputStr++) != '\n') {
		dwBoundaryCount++;
		dwHeaderCount++;
	}
	dwBoundaryCount--; 
	dwHeaderCount++;	
	
	for (dwLineIndex=0; dwLineIndex < 3;) {
		while (*(szInputStr++) != '\n') {
			dwHeaderCount++;
		}	
		dwHeaderCount++;
		dwLineIndex++;
	}
	dwCntLength = dwCntLength - dwHeaderCount - 2 - dwBoundaryCount - 4; 

    /*  EXTRACT_PATH: /tmp/etc.tar.bz2  */
	if((fpOutput=fopen(EXTRACT_PATH, "wb"))==NULL) {
		return -1;
	}

    /*将读取的数据以bz2包的形式存储*/
	fwrite(szInputStr, dwCntLength, 1, fpOutput);
	fclose(fpOutput);

    /*释放收集的内存区域*/
	free(pbyTemp);
	
	if ((pid = fork()) == 0) {
		// child process
		if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {  
			dup2(fd, STDIN_FILENO);  
			dup2(fd, STDOUT_FILENO);  
			dup2(fd, STDERR_FILENO);  
			if (fd > 2) {
				close(fd);
			}
		} 
		execl("/bin/tar", "tar", "-xzvf", "/tmp/etc.tar", "-C", "/", NULL);
	}     
    else { 
          // parent
          /*父进程等待子进程结束*/
		  wait4(pid, &status, 0, &rusage);
		  if(WIFEXITED(status)) {
              /*The child process terminated normally!*/
              printf("<html><body>");
              printf("<script> alert(\"Success!\"); window.parent.document.getElementById(\"destination\").src = \"/setup/maintaince.html\";</script>");
              printf("</body></html>");      
		  }
          else{
              printf("<html><body>");
              printf("<script>alert(\"Fail!\"); window.parent.document.getElementById(\"destination\").src = \"/setup/maintaince.html\";</script>");
              printf("</body></html>");      
          }
	} 
    return 0;
}

