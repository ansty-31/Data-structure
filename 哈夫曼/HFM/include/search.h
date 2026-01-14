#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>


#define MAX_LINE_LENGTH 1024          // 每行最大长度
#define MAX_PARAGRAPH_LENGTH 102400   // 每段最大长度
#define MAX_TARGETS 100               // 最大目标字符串数量

// 函数声明
int contains_any_string(const char *paragraph, char **targets, int target_count);   // 检查是否包含任意目标
int contains_all_strings(const char *paragraph, char **targets, int target_count);  // 检查是否包含所有目标
int is_empty_line(const char *line);                                                // 检查是否为空行
void search(const char *filename);                            // 处理文件并打印搜索结果

#endif