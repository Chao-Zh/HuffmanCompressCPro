#pragma once
#include <iostream>
using namespace std;

class huffNode
{
public:
    int weight;
    int pa;
    int lc;
    int rc;
};

void select(huffNode* hf,int n,int &id1,int &id2);

void CreateHuffTree(huffNode* hf,int n,int* wt);

void test01();

void TestHufTree(huffNode* pHT, int num);

void TestHuffTreeN(int root, huffNode* ht, int num);
void TestHufTreeN(int root, huffNode* pHT);

//函数声明里面不能有默认值
void HuffmanCoding(int root,huffNode* ht,int num,string HufCode[],string str);
