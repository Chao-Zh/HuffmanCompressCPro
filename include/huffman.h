#pragma once
#include <iostream>
#include <string>
using namespace std;

class huffNode
{
public:
    int weight;
    int pa;
    int lc;
    int rc;
};

void select(huffNode* hf, int n, int &id1, int &id2);

void CreateHuffTree(huffNode* hf, int n, int* wt);

void HuffmanCoding(int root, huffNode* ht, int num, string HufCode[], string str = "");