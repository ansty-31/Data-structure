#ifndef FREQUENCY_H
#define FREQUENCY_H

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#define MAX_CHARS 65536

// 统计信息结构体
typedef struct 
{
	int ch;  // 字符的Unicode码点
	int cnt; // 该字符出现的次数
	double freq;  // 该字符出现的频度
} Stat;

int count_char_freq(FILE *fp, int count[MAX_CHARS], int *total); // 统计字符频度
void print_freq(const int count[MAX_CHARS], int total);  // 输出频度统计结果
int cmp_stat_desc(const void *a, const void *b);  // 频度比较函数

#endif
