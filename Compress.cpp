#include <iostream>
using namespace std;
#include <cstring>
#include "Compress.h"
#include "huffman.h"
#define SIZE 10

int Compress(huffNode* ht,int* weight,const char* filename,string* HufCode)
{
    CreateHuffTree(ht, 256, weight);

    HuffmanCoding(510,ht,511,HufCode,"");
    int nSize=0;
    for(int i=0;i<256;++i) nSize+=weight[i]*HufCode[i].length();
    nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
    char* pBuffer=NULL;
    Encode(filename,HufCode,pBuffer,nSize);
    if(!pBuffer) return -1;
    HEAD sHead;
    InitHead(filename,sHead);
    int len = WriteFile(filename,sHead,pBuffer,nSize);
    return len;
}

int Str2byte(string pBinStr)
{
    int b = 0x00;
    while(pBinStr.size()<8) pBinStr+="0";
    for(int i = 0; i < 8; i++)
    {
        b = b<<1;// 左移 1 位
        if (pBinStr[i] == '1') {
            b = b | 0x01;
        }
    }
    return b;
}

int Encode(const char* filename,string* HufCode,char* &pBuffer,const int nSize)
{
    FILE *in = fopen(filename, "rb");
    pBuffer = (char*)malloc(nSize*sizeof(char));
    if (!pBuffer)
    {
        cerr<<"开辟缓冲区失败"<<endl;
        return -1;
    }
    string cd="";
    int pos=0;// 缓冲区指针
    int ch;
    while((ch=fgetc(in))!=EOF)
    {
        cd+=HufCode[ch];
        while(cd.size()>=8)
        {
            pBuffer[pos++]=Str2byte(cd);
            cd=cd.substr(8,sizeof(cd)-8);
        }
    }
    fclose(in);
    if(cd.length()>0) pBuffer[pos++]=Str2byte(cd);
}

int InitHead(const char *filename, HEAD &sHead)
{
    strcpy(sHead.type,"HUF");
    sHead.length=0;
    for(int i=0;i<256;++i) sHead.weight[i]=0;
    FILE* in =fopen(filename,"rb");
    int ch;
    while((ch = fgetc(in)) != EOF)
    {
        sHead.weight[ch]++;
        sHead.length++;
    }
    fclose(in);
    in=NULL;
    return 0;
}

int WriteFile(const char *pFilename, const HEAD sHead, const char* pBuffer, const int nSize)
{
    // 生成文件名
    char filename[256] = {0};
    strcpy(filename, pFilename);
    strcat(filename, ".huf");
    // 以二进制流形式打开文件
    FILE *out = fopen(filename, "wb");
    // 写文件头
    fwrite(&sHead, sizeof(HEAD), 1, out);
    // 写压缩后的编码
    fwrite(pBuffer, sizeof(char), nSize, out);
    // 关闭文件，释放文件指针
    fclose(out);
    out = NULL;
    cout<<"生成压缩文件:"<<filename<<endl;
    int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
    return len;
}
