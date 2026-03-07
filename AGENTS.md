# HuffmanCompressCPro 项目文档

## 项目概述

这是一个基于Huffman算法的C++文件压缩/解压缩程序。该程序实现了经典的Huffman编码压缩算法，能够对任意类型的文件进行无损压缩，并支持解压缩还原。

## 技术栈

- **语言**: C++ (C++17标准)
- **编译器**: GCC
- **开发环境**: VS Code (Linux)

## 项目结构

```
HuffmanCompressCPro/
├── main.cpp           # 主程序入口
├── huffman.h          # Huffman树相关函数声明
├── huffman.cpp        # Huffman树实现
├── Compress.h         # 压缩功能声明
├── Compress.cpp       # 压缩功能实现
├── DeCode.h           # 解压缩功能声明
├── DeCode.cpp         # 解压缩功能实现
└── .vscode/           # VS Code配置
    ├── tasks.json     # 构建任务配置
    ├── c_cpp_properties.json
    ├── launch.json
    └── settings.json
```

## 核心模块

### 1. Huffman树模块 (huffman.h/cpp)
- **数据结构**: `huffNode` 类表示Huffman树的节点
  - `weight`: 节点权重
  - `pa`: 父节点索引
  - `lc`: 左子节点索引
  - `rc`: 右子节点索引

- **核心函数**:
  - `select(huffNode* hf, int n, int &id1, int &id2)`: 选择权重最小的两个节点
  - `CreateHuffTree(huffNode* hf, int n, int* wt)`: 构建Huffman树
  - `HuffmanCoding(int root, huffNode* ht, int num, string HufCode[], string str)`: 生成Huffman编码

### 2. 压缩模块 (Compress.h/cpp)
- **数据结构**: `HEAD` 结构体存储压缩文件头信息
  - `type[4]`: 文件类型标识
  - `length`: 原始文件长度
  - `weight[256]`: 各字节频率统计

- **核心函数**:
  - `Compress(huffNode* ht, int* weight, const char* filename, string* HufCode)`: 执行压缩
  - `Str2byte(string pBinStr)`: 二进制字符串转字节
  - `Encode(const char* filename, string* HufCode, char* &pBuffer, const int nSize)`: 编码压缩
  - `InitHead(const char *filename, HEAD &sHead)`: 初始化文件头
  - `WriteFile(const char *pFilename, const HEAD sHead, const char* pBuffer, const int nSize)`: 写入压缩文件

### 3. 解压缩模块 (DeCode.h/cpp)
- **核心函数**:
  - `Byte2Str(int ch)`: 字节转二进制字符串
  - `DeCode(const char* filename, string* HufCode)`: 执行解压缩

### 4. 主程序 (main.cpp)
程序流程:
1. 用户输入要压缩的文件名
2. 统计文件中各字节的频率
3. 构建Huffman树
4. 生成Huffman编码
5. 执行压缩并生成 `.huf` 文件
6. 显示压缩率和文件大小
7. 提供解压缩选项

## 构建与运行

### 编译项目

**方法1: 使用VS Code任务**
- 使用 `Ctrl+Shift+P` 或按 `F1` 打开命令面板
- 输入 "Tasks: Run Task"
- 选择 "C/C++: g++ 生成活动文件"

**方法2: 手动编译**
```bash
cd /home/chaoz/vscodeprogram/HuffmanCompressCPro
g++ -g -fdiagnostics-color=always *.cpp -o a.exe
```

### 运行程序

```bash
./a.exe
```

运行后会提示输入要压缩的文件名，程序将执行压缩并显示压缩率。

## 压缩文件格式

压缩文件（`.huf`）结构:
```
[文件头 HEAD]
[压缩数据]
```

文件头包含:
- 4字节文件类型标识
- 原始文件长度（4字节）
- 256个字节的频率统计表

## 使用示例

```bash
# 编译程序
g++ -g *.cpp -o a.exe

# 运行程序
./a.exe

# 程序交互示例:
# ==========Huffman文件压缩系统==========
# 请输入文件名: pic.bmp
# 原文件大小:12345字节
# 压缩文件大小:8765字节
# 压缩率:71.0032%
# 是否解压文件? 是-1, 否-0
```

## 开发说明

- **编译器版本**: GCC (支持C++17标准)
- **标准**: GNU++17
- **字符编码**: 源代码使用GBK编码（中文注释）
- **调试**: 编译时包含 `-g` 标志以支持调试

## 已知限制

1. 源代码中的中文注释使用GBK编码，在UTF-8环境下可能显示乱码
2. 当前版本为命令行交互式程序，暂不支持批量处理
3. 压缩文件输出固定为 `.huf` 扩展名

## 测试文件

项目包含以下测试图片文件:
- `pic.bmp`
- `pic1.bmp`
- `pic2.bmp`
- `123.webp`
- `R-C.jpeg`

这些文件可用于测试压缩效果。通常BMP格式的图片压缩效果较好（因存在大量重复数据）。