#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h> 
#include <locale.h>

#include "Frequency.h"

#define MAX_CHARS 65536

//  哈夫曼码表项
typedef struct 
{
    int    ch;       // 字符
    double freq;     // 频度
    char  *bits;     // 哈夫曼编码字符串
} HuffmanCode;

//  哈夫曼树节点
typedef struct HeapNode 
{
    int    ch;     
    double freq;
    struct HeapNode *left;
    struct HeapNode *right;
} HeapNode;

// 最小堆结构
typedef struct 
{
    HeapNode **data;
    int size;   // 当前堆大小
    int cap;    // 堆容量
} MinHeap;

// 最小堆相关操作
MinHeap *create_heap(int cap); // 创建最小堆
void swap_node(HeapNode **a, HeapNode **b); // 交换堆节点指针
void heapify_down(MinHeap *h, int i);   // 堆下滤
void heap_push(MinHeap *h, HeapNode *node);  // 堆入栈
HeapNode *heap_pop(MinHeap *h);  // 堆出栈

// 哈夫曼树相关操作
HeapNode *build_tree(const int count[MAX_CHARS]); // 构建哈夫曼树
void gen_codes(HeapNode *root, char *buf, int depth, HuffmanCode *tbl, int *idx); // 生成哈夫曼编码表

// 频度比较函数（降序）
int cmp_desc(const void *a, const void *b);

// 哈夫曼编码相关操作
HuffmanCode *build_huffman_table(const int count[MAX_CHARS], int *pSize); // 构建哈夫曼码表
void output_huffman_table(const HuffmanCode *table, int size, int total);  // 输出哈夫曼码表
const char *get_huffman_bits(int ch, HuffmanCode *table, int size); // 生成哈夫曼编码比特串
int output_huffman_bitstream(const char *src, const char *dest, HuffmanCode *table, int size); // 输出哈夫曼编码比特流文件
void free_huffman_table(HuffmanCode *table, int size); // 释放哈夫曼码表内存

// 哈夫曼解码相关操作
HeapNode *rebuild_huffman_tree(const int count[MAX_CHARS]); // 重建哈夫曼树
int huffman_decode_file(const char *bin, const char *out, HeapNode *tree); // 哈夫曼解码文件
int compare_files_simple(const char* file1_path, const char* file2_path) ;// 简单文件比对

#endif

