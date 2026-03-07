#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "huffman.h"
#include "Compress.h"
#include "DeCode.h"
using namespace std;

int main()
{
    cout << "==========Huffman鏂囦欢鍘嬬缉绯荤粺==========" << endl;
    cout << "璇疯緭鍏ユ枃浠跺悕: ";
    char filename[256];
    cin >> filename;
    int weight[256] = {0};
    FILE *in = fopen(filename, "rb");
    if(in==NULL)
    {
        cout << "鏂囦欢涓嶅瓨鍦�锛�" << endl;
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
    cout << "鍘熸枃浠跺ぇ灏�: " << count << " 瀛楄妭" << endl;
    huffNode ht[511];
    string HufCode[256];
    int len = Compress(ht, weight, filename, HufCode);
    if(len <= 0)
    {
        cout << "鍘嬬缉澶辫触锛�" << endl;
        return 0;
    }
    cout << "鍘嬬缉鏂囦欢澶у皬: " << len << " 瀛楄妭" << endl;
    float f = (float)len / count * 100;
    printf("鍘嬬缉鐜囷細%.4lf%%\n", f);
    
    int choice = 0;
    cout << "鏄�鍚﹁В鍘嬫枃浠�? 鏄�-1, 鍚�-0: ";
    cin >> choice;
    if(choice != 1) return 0;
    
    // 鏋勯€犲帇缂╂枃浠跺悕
    char hufFilename[300];
    strcpy(hufFilename, filename);
    strcat(hufFilename, ".huf");
    DeCode(hufFilename, HufCode);
    return 0;
}