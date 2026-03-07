#include <iostream>
using namespace std;
#include "huffman.h"
#include "Compress.h"
#include <cstring>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

string Byte2Str(int ch)
{
    string arr="";
    int temp=ch;
    for(int i=7;i>=0;--i)
    {
        if(temp%2==1) arr="1"+arr;
        else arr="0"+arr;
        temp=temp>>1;
    }
    return arr;
}

void myWrite(string val)
{
    cout<<Str2byte(val)<<endl;
}

void DeCode(const char* filename,string* HufCode)
{
    char* oFilename="DeCode.bmp";
    FILE* out=fopen(oFilename,"wb");
    FILE* in=fopen(filename,"rb");
    map<string,int> hufCodeMap;
    for(int i=0;i<256;++i)
    {
        hufCodeMap[HufCode[i]]=i;
    }
    HEAD sHead;
    cout<<"正在生成文件:"<<oFilename<<endl;
    fread(&sHead, sizeof(HEAD), 1, in);
    vector<int> picData;
    cout<<"文件头读取成功，正在读取压缩文件数据。。。"<<endl;
    set<int> idx;
    for(int i=0;i<256;++i)
    {
        if(sHead.weight[i]!=0) idx.insert(i);
    }
    // int weight={0};
    string str="";
    int ch;
    int size=0;
    while((ch=fgetc(in))!=EOF)
    {
        str+=Byte2Str(ch);
        ++size;
    }
    cout<<"压缩文件数据读取成功，正在转码。。。"<<endl;
    // int count=0;
    int sign=1;
    int len=0;
    while(str.size()>0)
    {
        sign=1;
        for(int i:idx)
        {
            if(str.find(HufCode[i],len)==len)
            {
                picData.push_back(hufCodeMap[HufCode[i]]);
                len+=HufCode[i].size();
                --sHead.weight[i];
                if(sHead.weight[i]==0) idx.erase(i);
                sign=0;
                break;
            }
        }
        if(sign) break;
        cout<<"转码进度: "<<len/8<<"/"<<size<<endl;
    }
    cout<<"转码成功，正在写入缓冲区。。。"<<endl;
    char* oBuffer=(char*)malloc(sHead.length*sizeof(char));
    int pos=0;
    for(vector<int>::iterator it=picData.begin();it!=picData.end();++it)
    {
        oBuffer[pos++]=(char)(*(it));
    }
    cout<<"缓冲区写入成功！请稍等。。。"<<endl;
    fwrite(oBuffer,sHead.length,1,out);
    cout<<"解压成功！"<<endl;
    fclose(out);
    fclose(in);
    system("pause");
}