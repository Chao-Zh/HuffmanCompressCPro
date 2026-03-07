#pragma once
#include <iostream>
using namespace std;
#include "huffman.h"

int Compress(huffNode* ht,int* weight,const char* filename,string* HufCode);
int Str2byte(string pBinStr);
int Encode(const char* filename,string* HufCode,char* &pBuffer,const int nSize);

struct HEAD
{
    char type[4];
    int length;
    int weight[256];
};

int InitHead(const char *filename, HEAD &sHead);
int WriteFile(const char *pFilename, const HEAD sHead, const char* pBuffer, const int nSize);