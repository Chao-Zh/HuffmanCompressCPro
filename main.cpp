#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "huffman.h"
#include "Compress.h"
#include "DeCode.h"
using namespace std;

int main()
{
    cout << "==========Huffman文件压缩==========" << endl;
    cout << "请输入文件名:";
    char filename[256];
    cin >> filename;
    int weight[256] = {0};
    FILE *in = fopen(filename, "rb");
    if(in==NULL)
    {
        cout<<"文件不存在！"<<endl;
        system("pause");
        return 0;
    }
    int ch;
    int count=0;
    while ((ch = fgetc(in)) != EOF)
    {
        ++weight[ch];
        ++count;
    }
    fclose(in);
    cout<<"原文件大小:"<<count<<"字节"<<endl;
    huffNode ht[511];
    string HufCode[256];
    int len = Compress(ht,weight,filename,HufCode);
    cout<<"压缩文件大小:"<<len<<"字节"<<endl;
    float f = (float)len/count *100;
    printf("压缩比率：%.4lf%%\n",f);
    system("pause");
    int choice=0;
    cout<<"是否解压文件? 是-1, 否-0"<<endl;
    cin>>choice;
    choice=1;
    if(choice!=1) return 0;
    DeCode(strcat(filename,".huf"),HufCode);
    return 0;
}