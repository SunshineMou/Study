/***snake.c***/     
#include <stdio.h>     
#include <stdlib.h>  
#include <string.h>  
//#include <sys/time.h>     
#include <sys/types.h>     
#include <termio.h>     
#include <fcntl.h>     
#include <unistd.h>  

/*用于定义蛇头的初始位置*/
#define SNAKE_INITX   5     
#define SNAKE_INITY   5     
#define SNAKE_SHAPE   '*'     
#define SNAKE_INITLEN 8     

#define WIN_X1        1     
#define WIN_X2        80     
#define WIN_Y1        1     
#define WIN_Y2        24     

#define MAX_LEVEL     20     
#define MAX_INTER     200000     
#define MIN_INTER     0     
#define MAX_RICH      10     
#define DEVRATE       5     
#define OVER          "Game Over!!!"     

struct stNode     
{     
    int x;     
    int y;     
    char shape;     
    struct stNode *next;     
};     

/*食物的位置*/
struct stFood     
{     
    int x;     
    int y;     
};     

/*蛇头和蛇尾的链表指针*/
struct stNode *gpstHead,*gpstTail;

struct stFood gastFood[MAX_RICH];

int giLevel=1;     
int giRich=1;     
int giScore=0;     
int giLen=0;     

void settty(int iFlag)     
{     
    int fd;     
    struct termio stTerm;     
    
    /*
     *char *ttyname(int fd)  返回一个指向NULL结尾的终端设备的路径的字符串，这个设备通过文件描述符fd打开；
     */
    if((fd = open(ttyname(1),O_RDWR))==-1)        
        return;     
    if(iFlag == 1)     
    {     
        ioctl(fd,TCGETA,&stTerm);
        /*局部模式*/     
        stTerm.c_lflag &= ~ICANON; /*禁用标准模式*/    
        stTerm.c_lflag &= ~ECHO;   /*阻止键入字元的回应*/     
       
        /*特殊控制字元*/ 
        stTerm.c_cc[4] = 1;     
        stTerm.c_cc[5] = 0;     
        
        /*输入模式*/
        stTerm.c_iflag &= ~ISTRIP; /*禁止去掉第8位*/

        /*控制模式*/     
        stTerm.c_cflag |= CS8;     /*传送或接收字元时用的位数*/     
        stTerm.c_cflag &= ~PARENB; /*禁止输出产生奇偶信息及输入奇偶校验*/    

        ioctl(fd,TCSETA,&stTerm);     
    }     
    else     
    {     
        ioctl(fd,TCGETA,&stTerm);     
        stTerm.c_lflag |= ICANON;     
        stTerm.c_lflag |= ECHO;     
        stTerm.c_cc[4] = 4;     
        stTerm.c_cc[5] = 5;     
        stTerm.c_iflag &= ~ISTRIP;     
        stTerm.c_cflag |= CS8;     
        stTerm.c_cflag &= ~PARENB;     
        ioctl(fd,TCSETA,&stTerm);     
    }     
    close(fd);     
}     

/*!
 * \brief   在终端的某个指定的位置显示一个点(用于蛇身的显示)
 *
 * \param pstNode
 * \param iFlag
 */
void vDrawOneNode(struct stNode *pstNode,int iFlag)     
{
    /*  调用函数的iFlag为：1  */    
    printf("\033[%dm\033[%dm\033[%d;%dH%c\033[0m",   
            iFlag, iFlag*3+8, pstNode->y, pstNode->x, pstNode->shape);   
    /*printf("\033[%d;%dH%c", pstNode->y, pstNode->x, pstNode->shape);    */
    fflush(stdout);     
}     

/*!
 * \brief   在终端的某个位置上显示蛇的一个食物
 *
 * \param x
 * \param y
 */
void vDrawOneFood(int x,int y)     
{     
    /*printf("\033[1m\033[40;36m\033[%d;%dH%c", y, x, '@');     */
    printf("\033[%d;%dH%c", y, x, '$');     
    fflush(stdout);     
}     


int iGetDir(int iOriDir)     
{     
    fd_set  rset;     
    struct  timeval  hTmo;     
    int     iRet, iFlag=0;     
    char    cCh;     

    FD_ZERO(&rset);     
    FD_SET(0,&rset);     
    
    /*
     *#define MAX_LEVEL     20     
     *#define MAX_INTER     200000     
     *#define MIN_INTER     0     
     */
    
    hTmo.tv_sec=0;     
    hTmo.tv_usec = MAX_INTER-(MAX_INTER-MIN_INTER)/MAX_LEVEL*giLevel;     

    iRet=select(1,&rset,NULL,NULL,&hTmo);

    if(iRet==0)     
    {     
        return(iOriDir);     
    }     
    for(;;)     
    {     
        cCh=getchar();     
        if(cCh != -1)     
        {     
            switch(cCh)     
            {              
                case 27  :     
                case 91  :     
                    iFlag++;     
                    break;     
                case 65 :   //UP     
                case 66 :   //DOWN     
                case 67 :   //RIGHT     
                case 68 :   //LEFT     
                    if(iFlag==2)     
                        return((!((cCh-0x41) ^ iOriDir ^ 1)) ^ (cCh-0x41));     
                default  :     
                    return(iOriDir);     
            }     
        }     
    }     
} 


/*!
 * \brief    对控制终端进行设置操作
 */
void vInitScreen()     
{     
    settty(1);     
    printf("\033[?25l\033[2J");     /*隐藏光标并清屏*/     
}     

void vRestoreScreen()     
{     
    printf("\033[24;1H\033[?25h");     
    settty(0);     
}     

/*!
 * \brief   对终端的视野进行设置操作
 */
void vDrawScope()     
{     
    int i,j;   

    /*
     *  #define WIN_X1 1     
     *  #define WIN_X2 80     
     *  #define WIN_Y1 1     
     *  #define WIN_Y2 24     
     */

    for(j = WIN_Y1; j <= WIN_Y2; j += WIN_Y2-WIN_Y1)     
    {    
        /* \033[y;xH ---> 设置光标的位置*/ 
        printf("\033[%d;%dH+",j,WIN_X1);     
        for(i = WIN_X1+1; i < WIN_X2; i++)     
            printf("=");     
        printf("+");     
    }     
    for(i = WIN_Y1+1; i < WIN_Y2; i++)     
        printf("\033[%d;%dH+%*c+\n", i, WIN_X1, WIN_X2-WIN_X1-1, ' ');     
}     

void vCreateSnake()     
{     
    struct stNode *pstNew;     
    int i; 

    /*
     *  #define SNAKE_INITX 5    
     *  #define SNAKE_INITY 5    
     *  #define SNAKE_SHAPE '*'    
     *  #define SNAKE_INITLEN 8  -- 定义蛇的初始化长度为8个node    
     */

    gpstHead=(struct stNode*)malloc(sizeof(struct stNode));     
    gpstHead->x=SNAKE_INITX;     /*初始化时X轴所在位置*/       
    gpstHead->y=SNAKE_INITY;     /*初始化时Y轴坐在位置*/
    gpstHead->shape=SNAKE_SHAPE; /*定义蛇头的形状*/    
    gpstHead->next=NULL;     
    vDrawOneNode(gpstHead,1);    /*蛇头在终端上的显示*/     
    gpstTail=gpstHead;           /*初始化时只有一个点，所以蛇头和蛇尾的数据相同*/ 
    for(i=1;i<SNAKE_INITLEN;i++)     
    {     
        pstNew=(struct stNode*)malloc(sizeof(struct stNode));     
        pstNew->x=gpstHead->x+1;            
        pstNew->y=gpstHead->y;     
        pstNew->shape=SNAKE_SHAPE;     
        pstNew->next=NULL;     
        vDrawOneNode(pstNew,1);     
        gpstHead->next=pstNew;     
        gpstHead=pstNew;     
    }     
    return;     
}     

void vKillSnake()     
{     
    struct stNode *pstNode;     

    for(pstNode=gpstTail;gpstTail!=NULL;)     
    {     
        gpstTail=pstNode->next;     
        free(pstNode);     
        pstNode=gpstTail;     
    }     
}     

void vGenFood(int iIdx)     
{     
    struct stNode *pstNode;     
    int i,iFound=0;     

    /* 注意此处for循环的使用方法--应该与while循环相似 */
    for(;!iFound;)     
    {     
        iFound=1;    
        /* 
         * 对于y轴坐标来讲:
         * 经过rand产生一个随机数对22进行取余，所得到的数在0-21之间；在经过后面的运算，这个数的范围就在2-23之间
         * 而边界正好在1-24之间；
         */ 
        gastFood[iIdx].x=rand()%(WIN_X2-WIN_X1-1)+WIN_X1+1;     
        gastFood[iIdx].y=rand()%(WIN_Y2-WIN_Y1-1)+WIN_Y1+1;    

        for(i=0;i<giRich;i++)     
        {  
            /*如果产生的随机数已经存在，则将iFound置为0，重新开始循环*/   
            if(i!=iIdx && gastFood[iIdx].x == gastFood[i].x && gastFood[iIdx].y == gastFood[i].y)     
            {     
                iFound=0;     
                break;     
            }     
        }     
        if(!iFound) 
            continue;     
        for(pstNode=gpstTail;pstNode!=NULL;pstNode=pstNode->next)     
        {     
            if(gastFood[iIdx].x == pstNode->x && gastFood[iIdx].y == pstNode->y)     
            {     
                iFound=0;     
                break;     
            }     
        }     
        if(!iFound) 
            continue;     
    }     
    vDrawOneFood(gastFood[iIdx].x,gastFood[iIdx].y);     
}     

void vInitFood()     
{     
    int i;     

    srand(getpid());     
    for(i = 0; i < giRich; i++)        
        vGenFood(i);     
}     

/*!
 * \brief   判断此时x，y的值是否在所规定的范围内，是返回1；否则返回0；
 *
 * \param x
 * \param y
 *
 * \return 
 */
int iIsValid(int x,int y)     
{     
    struct stNode *pstNode;     
    
    /*如果x,y的值不在我们定义的区间内，则表示游戏失败*/
    if(x == WIN_X1 || x >= WIN_X2 || y == WIN_Y1 || y >= WIN_Y2)     
        return(0);     
    pstNode = gpstTail;     
    for(;pstNode!=NULL;)     
    {     
        if(x == pstNode->x && y == pstNode->y)     
            return(0);     
        pstNode = pstNode->next;     
    }     
    return(1);     
}     

int iEat(int x,int y)     
{     
    int i;     

    for(i=0;i<giRich;i++)     
    {   
        /*如果此时的x,y坐标位置已是食物中的一员，则再次产生食物*/  
        if(x == gastFood[i].x && y == gastFood[i].y)     
        {     
            vGenFood(i);     
            giScore+=giLevel*10;     
            giLen++;     
            if(giLevel<MAX_LEVEL)     
                if(giLen%DEVRATE == 0)     
                    giLevel++;     
            return(1);     
        }     
    }     
    return(0);     
}     

/*!
 * \brief   主程序：有关链表的操作，应该是gpstHead为链表尾，gpsTail为链表头
 *
 * \return 
 */
int main()     
{     
    int iDir=2,iNextX,iNextY;     
    struct stNode *pstNew;     
    char sPrompt[80];     

    vInitScreen();     
    vDrawScope();     
    vCreateSnake();     
    vInitFood();     
    for(;;)     
    {     
        iDir=iGetDir(iDir); 
        /*以原来蛇头的x,y基数为准，确定新位置的坐标*/    
        iNextX=gpstHead->x+(iDir>>1)*(5-(iDir<<1));     
        iNextY=gpstHead->y-(!(iDir>>1))*(1-(iDir<<1));
        /* 如果数据无效，则表示游戏失败，打印Game Over！！信息 */     
        if(!iIsValid(iNextX,iNextY))     
        {     
            printf("\033[%d;%dH%s\033[0m",     
                    WIN_Y2-1,(WIN_X1+WIN_X2)/2-strlen(OVER)/2,OVER);     
            break;     
        }     
        pstNew=(struct stNode*)malloc(sizeof(struct stNode));     
        pstNew->x=iNextX;     
        pstNew->y=iNextY;     
        pstNew->shape=SNAKE_SHAPE;    
        /*pstNew->shape='#';     */
        pstNew->next=NULL;     
        gpstHead->next=pstNew;     
        gpstHead=pstNew;     
        vDrawOneNode(gpstHead,1);

        /*如果没有吃到食物,在头部增加一个显示之后，对应的尾部还要清除掉一个显示，以维持蛇的长度*/     
        if(!iEat(iNextX,iNextY))     
        {     
            /*vDrawOneNode(gpstHead,1);     */
            vDrawOneNode(gpstTail,0);
            
            pstNew=gpstTail;     
            gpstTail=pstNew->next;     
            free(pstNew);     
        }   

        /* 打印窗口下面的积分和级别的信息*/
        sprintf(sPrompt,"Score:%7d Level:%2d",giScore,giLevel);     
        printf("\033[%d;%dH%s\033[0m",     
                WIN_Y2,(WIN_X1+WIN_X2)/2-strlen(sPrompt)/2,sPrompt);   

    }     
    vKillSnake();     
    vRestoreScreen();     
    return 0;  
}    
