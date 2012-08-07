/*!
 * \file	bitmap.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-04-01 15:27:26
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1)
typedef struct tagBITMAPFILEHEADER
{
    unsigned short int bfType;
    unsigned       int bfSize;
    unsigned short int bfReserved1;
    unsigned short int bfReserved2;
    unsigned       int bfOffBits;
}BITMAPFILEHEADER;

//定义位图信息头
typedef struct tagBITMAPINFOHEADER
{
    unsigned int       biSize;
    int                biWidth;
    int                biHeight;
    unsigned short int biPlanes;
    unsigned short int biBitCount;
    unsigned int       biCompression;
    unsigned int       biSizeImage;
    int                biXPelsPerMeter;
    int                biYPelsPerMeter;
    unsigned int       biClrUsed;
    unsigned int       biClrImportant;
}BITMAPINFOHEADER;

//定义调色板/真彩色位图的RGB数据
typedef struct tagRGBQUAD
{
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
}RGBQUAD;

//定义位图文件
typedef struct tagBITMAP
{
    BITMAPFILEHEADER bmpHeader;
    BITMAPINFOHEADER bmpInfoHeader;
    RGBQUAD          RGB[1024*684];
}BITMAP;

//定义8位灰度位图文件
typedef struct tag8BITMAP
{ 
    BITMAPFILEHEADER bmpHeader;
    BITMAPINFOHEADER bmpInfoHeader;
    RGBQUAD          RGB[256];
    unsigned char    bmpRGBBLOCK[1024*684];
}BITMAP_8BIT;
#pragma pack()        

//定义一个存储bmp图像数据的全局变量
BITMAP  bmpMap;                                                                                                     
BITMAP_8BIT bmpMap8;                                                                                                                                

//读取位图文件并打印相关信息                                                                                                     
int ReadBITMAP(char *source, char *destination);

int main(int argc, char* argv[])
{
    if(argc!=3)
    {
        printf("Usage:bmp.out source destination\n");
        return -1;
    }
    if(ReadBITMAP(argv[1],argv[2]) == -1)
        printf("Error in converting the bitmap!\n");
    printf("Success in converting the bitmap!\n"); 
    printf("Size:%d\n",sizeof(bmpMap.bmpHeader));
    return 0;
}

int ReadBITMAP(char *source, char *destination)
{   
    FILE *fp;
    FILE *fp1;
    fp=fopen(source,"r");
    if(fp==NULL)
    {
        printf("There is an error in opening the photograph!\n");
        return -1;
    }
    else
        printf("Success! We have opened a bmp photo!\n");
    if(fread(&bmpMap,sizeof(bmpMap),1,fp) == 0)
    {
        printf("Error in open the bitmap1!\n");
        return -1;
    }
    fclose(fp);
    fp1=fopen(source,"r"); 
    if(fread(&bmpMap8,54,1,fp1) == 0)
    {
        printf("Error in open the bitmap2!\n");
        return -1;
    }
    fclose(fp1);
    if(bmpMap.bmpHeader.bfType==0x4d42)
        printf("This is a %d bit bmp picture.\n",bmpMap.bmpInfoHeader.biBitCount);
    bmpMap8.bmpInfoHeader.biBitCount=0x0008;

    unsigned int i = 0;
    unsigned int j = 0;
    RGBQUAD *temp;  
    float rgbTemp;
    unsigned char  rgbFinal;
    FILE *bmp1;
    FILE *bmp2;
    for(i=0;i<256;i++)
    {
        bmpMap8.RGB[i].rgbBlue=i;
        bmpMap8.RGB[i].rgbGreen=i;
        bmpMap8.RGB[i].rgbRed=i;
    }
    for(temp=bmpMap.RGB;temp<bmpMap.RGB+1024*684;temp++,j++)
    {
        rgbTemp=(*temp).rgbBlue*0.114+(*temp).rgbGreen*0.587+(*temp).rgbRed*0.299;
        rgbFinal=(unsigned char)rgbTemp;
        (*temp).rgbBlue  =rgbFinal;
        (*temp).rgbGreen =rgbFinal;
        (*temp).rgbRed   =rgbFinal;
        bmpMap8.bmpRGBBLOCK[j]=rgbFinal;
    }
    if((bmp1=fopen(destination,"wb+")) == NULL)
    {
        printf("Open error!");
        return -1;
    }
    if((bmp2=fopen("/home/sunshine/sun.bmp","wb+")) == NULL)
    {
        printf("Open error!");
        return -1;
    }
    fwrite(&bmpMap8,sizeof(bmpMap8),1,bmp1);
    fwrite(&bmpMap,sizeof(bmpMap),1,bmp2);
    fclose(bmp1);
    fclose(bmp2);
    return 1;
}

