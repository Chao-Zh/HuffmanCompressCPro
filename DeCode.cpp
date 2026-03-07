#include <iostream>
using namespace std;
#include "huffman.h"
#include "Compress.h"
#include <cstring>
#include <map>
#include <vector>

string Byte2Str(int ch)
{
    string arr = "";
    int temp = ch;
    for(int i = 7; i >= 0; --i)
    {
        if(temp % 2 == 1) arr = "1" + arr;
        else arr = "0" + arr;
        temp = temp >> 1;
    }
    return arr;
}

void DeCode(const char* filename, string* HufCode)
{
    // 从输入文件名生成输出文件名（去掉.huf扩展名）
    char oFilename[300] = {0};
    strcpy(oFilename, filename);
    int len = strlen(oFilename);
    if(len > 4 && strcmp(oFilename + len - 4, ".huf") == 0)
    {
        oFilename[len - 4] = '\0';
    }
    strcat(oFilename, "_decoded");
    
    FILE* out = fopen(oFilename, "wb");
    FILE* in = fopen(filename, "rb");
    if(!in || !out)
    {
        cerr << "打开文件失败" << endl;
        if(in) fclose(in);
        if(out) fclose(out);
        return;
    }
    
    map<string, int> hufCodeMap;
    for(int i = 0; i < 256; ++i)
    {
        if(HufCode[i].length() > 0)
        {
            hufCodeMap[HufCode[i]] = i;
        }
    }
    
    HEAD sHead;
    cout << "输出解压文件: " << oFilename << endl;
    fread(&sHead, sizeof(HEAD), 1, in);
    cout << "文件头读取成功，正在读取压缩文件数据..." << endl;
    
    vector<int> picData;
    string str = "";
    int ch;
    while((ch = fgetc(in)) != EOF)
    {
        str += Byte2Str(ch);
    }
    cout << "压缩文件数据读取成功，开始解码..." << endl;
    
    // 使用更高效的解码算法
    int pos = 0;
    int totalBytes = sHead.length;
    int decodedBytes = 0;
    
    while(pos < (int)str.size() && decodedBytes < totalBytes)
    {
        bool found = false;
        string code = "";
        
        for(int i = pos; i < (int)str.size() && i - pos < 256; ++i)
        {
            code += str[i];
            if(hufCodeMap.find(code) != hufCodeMap.end())
            {
                int value = hufCodeMap[code];
                picData.push_back(value);
                pos = i + 1;
                decodedBytes++;
                found = true;
                break;
            }
        }
        
        if(!found) break;
        
        if(decodedBytes % 10000 == 0)
        {
            cout << "解码进度: " << decodedBytes << "/" << totalBytes << endl;
        }
    }
    
    cout << "解码成功，正在写入缓冲区..." << endl;
    char* oBuffer = (char*)malloc(sHead.length * sizeof(char));
    if(!oBuffer)
    {
        cerr << "分配内存失败" << endl;
        fclose(in);
        fclose(out);
        return;
    }
    
    for(int i = 0; i < (int)picData.size(); ++i)
    {
        oBuffer[i] = (char)picData[i];
    }
    
    cout << "缓冲区写入成功，正在写入文件..." << endl;
    fwrite(oBuffer, sHead.length, 1, out);
    cout << "解压成功！" << endl;
    
    free(oBuffer);
    fclose(out);
    fclose(in);
}