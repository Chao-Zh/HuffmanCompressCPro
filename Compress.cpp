#include <iostream>
using namespace std;
#include <cstring>
#include "Compress.h"
#include "huffman.h"

int Compress(huffNode* ht, int* weight, const char* filename, string* HufCode)
{
    CreateHuffTree(ht, 256, weight);
    HuffmanCoding(510, ht, 511, HufCode, "");
    
    int nSize = 0;
    for(int i = 0; i < 256; ++i)
    {
        nSize += weight[i] * HufCode[i].length();
    }
    nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
    
    char* pBuffer = NULL;
    if(Encode(filename, HufCode, pBuffer, nSize) < 0)
    {
        return -1;
    }
    if(!pBuffer) return -1;
    
    HEAD sHead;
    InitHead(filename, weight, sHead);
    int len = WriteFile(filename, sHead, pBuffer, nSize);
    
    // 閲婃斁鍐呭瓨
    free(pBuffer);
    return len;
}

int Str2byte(string pBinStr)
{
    int b = 0x00;
    while(pBinStr.size() < 8) pBinStr += "0";
    for(int i = 0; i < 8; i++)
    {
        b = b << 1;
        if (pBinStr[i] == '1')
        {
            b = b | 0x01;
        }
    }
    return b;
}

int Encode(const char* filename, string* HufCode, char* &pBuffer, const int nSize)
{
    FILE *in = fopen(filename, "rb");
    if(!in)
    {
        cerr << "鎵撳紑鏂囦欢澶辫触" << endl;
        return -1;
    }
    
    pBuffer = (char*)malloc(nSize * sizeof(char));
    if (!pBuffer)
    {
        cerr << "鍒嗛厤缂撳啿鍖哄け璐�" << endl;
        fclose(in);
        return -1;
    }
    
    string cd = "";
    int pos = 0;
    int ch;
    while((ch = fgetc(in)) != EOF)
    {
        cd += HufCode[ch];
        while(cd.size() >= 8)
        {
            pBuffer[pos++] = Str2byte(cd);
            cd = cd.substr(8);
        }
    }
    fclose(in);
    
    if(cd.length() > 0)
    {
        pBuffer[pos++] = Str2byte(cd);
    }
    return 0;
}

int InitHead(const char *filename, int* weight, HEAD &sHead)
{
    strcpy(sHead.type, "HUF");
    sHead.length = 0;
    for(int i = 0; i < 256; ++i)
    {
        sHead.weight[i] = weight[i];
        sHead.length += weight[i];
    }
    return 0;
}

int WriteFile(const char *pFilename, const HEAD sHead, const char* pBuffer, const int nSize)
{
    char filename[300] = {0};
    strcpy(filename, pFilename);
    strcat(filename, ".huf");
    
    FILE *out = fopen(filename, "wb");
    if(!out)
    {
        cerr << "鍒涘缓鍘嬬缉鏂囦欢澶辫触" << endl;
        return -1;
    }
    
    fwrite(&sHead, sizeof(HEAD), 1, out);
    fwrite(pBuffer, sizeof(char), nSize, out);
    fclose(out);
    
    cout << "鐢熸垚鍘嬬缉鏂囦欢: " << filename << endl;
    int len = sizeof(HEAD) + nSize;
    return len;
}