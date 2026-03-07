#include <iostream>
using namespace std;
#include "huffman.h"
#define INFINITY 0x7FFFFFFF

void select(huffNode* hf, int n, int &id1, int &id2)
{
    int min1 = INFINITY, min2 = INFINITY;
    id1 = id2 = -1;
    for(int i = 0; i < n; ++i)
    {
        if(hf[i].pa == -1 && hf[i].weight < min1)
        {
            id2 = id1;
            min2 = min1;
            min1 = hf[i].weight;
            id1 = i;
        }
        else if(hf[i].pa == -1 && hf[i].weight < min2)
        {
            min2 = hf[i].weight;
            id2 = i;
        }
    }
}

void CreateHuffTree(huffNode* hf, int n, int* wt)
{
    int m = 2 * n - 1;
    for(int i = 0; i < m; ++i)
    {
        hf[i].pa = -1;
        hf[i].lc = -1;
        hf[i].rc = -1;
        hf[i].weight = 0;
    }
    for(int i = 0; i < n; ++i)
    {
        hf[i].weight = wt[i];
    }
    int id1, id2;
    for(int i = n; i < m; ++i)
    {
        select(hf, i, id1, id2);
        hf[i].lc = id1;
        hf[i].rc = id2;
        hf[id1].pa = hf[id2].pa = i;
        hf[i].weight = hf[id1].weight + hf[id2].weight;
    }
}

void HuffmanCoding(int root, huffNode* ht, int num, string HufCode[], string str)
{
    if(root < 0 || root >= num) return;
    if(ht[root].lc == -1 && ht[root].rc == -1)
    {
        HufCode[root] = str;
        return;
    }
    HuffmanCoding(ht[root].lc, ht, num, HufCode, str + "0");
    HuffmanCoding(ht[root].rc, ht, num, HufCode, str + "1");
}