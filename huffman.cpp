#include <iostream>
using namespace std;
#include "huffman.h"
#define INFINITY 0x7FFFFFFF


void select(huffNode* hf,int n,int &id1,int &id2)
{
    int min1=INFINITY,min2=INFINITY;
    id1=id2=-1;//一定要初始化为这个值，表示暂未找到
    for(int i=0;i<n;++i)
    {
        if(hf[i].pa==-1 && hf[i].weight<min1)
        {
            id2=id1;min2=min1;//表示把最小传给次小
            min1=hf[i].weight;
            id1=i;
        }
        else if(hf[i].pa==-1 && hf[i].weight<min2)
        {
            min2=hf[i].weight;
            id2=i;
        }
    }
}

void CreateHuffTree(huffNode* hf,int n,int* wt)
{
    int m=2*n-1;
    for(int i=0;i<m;++i)
    {
        hf[i].pa=-1;
        hf[i].lc=-1;
        hf[i].rc=-1;
        hf[i].weight=0;
    }
    for(int i=0;i<n;++i) hf[i].weight=wt[i];
    int id1,id2;
    for(int i=n;i<m;++i)
    {
        select(hf,i,id1,id2);
        hf[i].lc=id1;
        hf[i].rc=id2;
        hf[id1].pa=hf[id2].pa=i;
        hf[i].weight=hf[id1].weight+hf[id2].weight;
    }
}

//测试哈夫曼树
void test01()
{
    huffNode hf[7];
    int weight[]={15,5,30,10};
    CreateHuffTree(hf,4,weight);
    for (int i = 0; i < 7; ++i)
    {
        cout<<i<<" "<<hf[i].weight<<" "<<hf[i].pa<<" "<<hf[i].lc<<" "<<hf[i].rc<<" "<<endl;
    }
}

void TestHufTree(huffNode* pHT, int num)
{
    for (int i = 0; i < num; ++i)
    {
        printf("pHT[%d]\t%d\t%d\t%d\t%d\n", i, pHT[i].weight, pHT[i].pa,
               pHT[i].lc, pHT[i].rc);
    }
}

void TestHuffTreeN(int root, huffNode* ht, int num)
{
    if (0 <= root && root < num)
    {
        cout << ht[root].weight << " ";
        TestHuffTreeN(ht[root].lc, ht, num);
        TestHuffTreeN(ht[root].rc, ht, num);
    }
}

// void TestHufTreeN(int root, huffNode* pHT)
// {
//     cout<<pHT[root].weight<<" ";
//     if(pHT[root].lc != -1)
//     {
//         TestHufTreeN(pHT[root].lc, pHT);
//     }
//     if(pHT[root].rc != -1)
//     {
//         TestHufTreeN(pHT[root].rc, pHT);
//     }
// }


//注意，某参数具有默认值，之后的参数都必须要有默认值
void HuffmanCoding(int root,huffNode* ht,int num,string HufCode[],string str="")
{
    if(root<0 || root>=num) return;
    if(ht[root].lc==-1 && ht[root].rc==-1)
    {
        HufCode[root]=str;
        return;
    }
    HuffmanCoding(ht[root].lc,ht,num,HufCode,str+"0");
    HuffmanCoding(ht[root].rc,ht,num,HufCode,str+"1");
}