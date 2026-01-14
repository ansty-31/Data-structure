#ifndef WORD_FREQ_H
#define WORD_FREQ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define HASH_SIZE 1000          // 哈希表大小
#define MAX_WORD_LEN 100        // 单词最大长度
#define MAX_LINE_LEN 1024       // 每行最大长度

// 哈希表节点结构
typedef struct WordNode 
{
    char word[MAX_WORD_LEN];
    int count;
    struct WordNode *next;      // 链表指针，解决哈希冲突
} WordNode;

// 常见单词和短词列表
extern const char *validShortWords[];
extern const int validShortWordCount;

// 哈希表（在.c文件中定义）
extern WordNode *hashTable[HASH_SIZE];

// 函数声明
bool isWordSeparator(char c);                           // 判断是否为单词分隔符
unsigned int hashFunc(const char *str);                 // 哈希函数
bool isValidWord(const char *word, const char *line, int start, int end); // 验证单词有效性
void insertWord(const char *word);                      // 插入或更新单词到哈希表
WordNode **collectWords(int *totalCount);               // 收集哈希表中的单词到数组
int compareAlpha(const void *a, const void *b);         // 比较函数（按字母顺序）
void freeHashTable(void);                               // 释放哈希表内存
void word_freq(const char *filename);    // 处理文件并打印统计结果

#endif // WORD_FREQ_H