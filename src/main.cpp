#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "../include/huffman.h"
#include "../include/Compress.h"
#include "../include/DeCode.h"
using namespace std;

int main()
{
    cout << "==========Huffman文件压缩系统==========" << endl;
    cout << "请输入文件名: ";
    char filename[256];
    cin >> filename;
    int weight[256] = {0};
    FILE *in = fopen(filename, "rb");
    if(in==NULL)
    {
        cout << "文件不存在！" << endl;
        return 0;
    }
    int ch;
    int count = 0;
    while ((ch = fgetc(in)) != EOF)
    {
        ++weight[ch];
        ++count;
    }
    fclose(in);
    cout << "原文件大小: " << count << " 字节" << endl;
    huffNode ht[511];
    string HufCode[256];
    int len = Compress(ht, weight, filename, HufCode);
    if(len <= 0)
    {
        cout << "压缩失败！" << endl;
        return 0;
    }
    cout << "压缩文件大小: " << len << " 字节" << endl;
    float f = (float)len / count * 100;
    printf("压缩率：%.4lf%%\n", f);
    
    int choice = 0;
    cout << "是否解压文件? 是-1, 否-0: ";
    cin >> choice;
    if(choice != 1) return 0;
    
    // 构造压缩文件名
    char hufFilename[300];
    strcpy(hufFilename, filename);
    strcat(hufFilename, ".huf");
    DeCode(hufFilename, HufCode);
    return 0;
}