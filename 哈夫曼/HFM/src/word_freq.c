#include "word_freq.h"

// 哈希表初始化
WordNode *hashTable[HASH_SIZE] = {NULL};
// 常见单词和短词验证
const char *validShortWords[] = 
{
    // 单字母单词
    "a", "i",
    // 双字母单词
    "am", "an", "as", "at", "be", "by", "do", "go", "he", "hi",
    "if", "in", "is", "it", "me", "my", "no", "of", "on", "or",
    "so", "to", "up", "us", "we"
};
const int validShortWordCount = sizeof(validShortWords) / sizeof(validShortWords[0]); // 有效短词数量
// 分隔符标定
bool isWordSeparator(char c) 
{
    // 空格、标点、数学运算符都是分隔符
    return isspace(c) || 
           strchr(".,;:!?()[]{}\"'", c) != NULL || // 标点符号
           strchr("=+-*/<>|&^%~_", c) != NULL;  // 包含数学运算符和下划线
}
//哈希函数
unsigned int hashFunc(const char *str) 
{
    unsigned int hash = 5381; // 使用DJB2哈希算法
    int c;
    while ((c = *str++)) 
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % HASH_SIZE;
}
// 验证单词有效性
bool isValidWord(const char *word, const char *line, int start, int end) 
{
    int len = strlen(word);
    if (len == 0) return false;
    // 检查是否全是字母或允许撇号
    for (int i = 0; i < len; i++) 
    {
        if (!isalpha(word[i]) && word[i] != '\'')   return false;
    }
    // 检查单词边界
    // 前一个字符必须是分隔符
    if (start > 0 && !isWordSeparator(line[start - 1])) return false;
    // 后一个字符必须是分隔符或字符串结束
    if (line[end] != '\0' && !isWordSeparator(line[end])) return false;
    // 处理短单词
    if (len <= 3) 
    {
        // 检查是否在有效短词列表中
        for (int i = 0; i < validShortWordCount; i++) 
        {
            if (strcmp(word, validShortWords[i]) == 0)  return true;
               
        }
        // 对于未在列表中的短单词
        if (len == 1) return false; // 只有a和i被接受，已在列表中
        // 对于2-3字母单词，排除明显是数学模式的
        if (len == 2) 
        {
            // 排除重复字母或连续字母模式
            if (word[0] == word[1] || abs(word[0] - word[1]) == 1)   return false;
        }
        // 其他短单词排除
        return false;
    }
    // 长度>=4的单词接受
    return true;
}
// 插入或更新单词
void insertWord(const char *word) 
{
    if (strlen(word) == 0) return;
    // 计算哈希值
    unsigned int index = hashFunc(word);
    WordNode *node = hashTable[index];
    // 查找单词是否已存在
    while (node != NULL) 
    {
        if (strcmp(node->word, word) == 0) 
        {
            node->count++;
            return;
        }
        node = node->next;
    }
    // 单词不存在，创建新节点
    WordNode *newNode = (WordNode *)malloc(sizeof(WordNode));
    if (newNode == NULL) 
    {
        fprintf(stderr, "内存分配失败\n");
        return;
    }
    strcpy(newNode->word, word);
    newNode->count = 1;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;  //头插法
}
// 收集单词到数组
WordNode **collectWords(int *totalCount) 
{
    // 计算总单词数
    int count = 0;
    for (int i = 0; i < HASH_SIZE; i++) 
    {
        WordNode *node = hashTable[i];
        while (node != NULL) 
        {
            count++;
            node = node->next;
        }
    }
    // 如果没有单词，返回NULL
    if (count == 0) 
    {
        *totalCount = 0;
        return NULL;
    }
    // 创建单词数组
    WordNode **wordArray = (WordNode **)malloc(count * sizeof(WordNode *));
    if (wordArray == NULL) 
    {
        fprintf(stderr, "内存分配失败\n");
        *totalCount = 0;
        return NULL;
    }
    // 填充单词数组
    int index = 0;
    for (int i = 0; i < HASH_SIZE; i++) 
    {
        WordNode *node = hashTable[i];
        while (node != NULL) 
        {
            wordArray[index++] = node;
            node = node->next;
        }
    }
    // 设置总数
    *totalCount = count;
    return wordArray;
}
// 比较函数
int compareAlpha(const void *a, const void *b) 
{
    WordNode *nodeA = *(WordNode **)a;
    WordNode *nodeB = *(WordNode **)b;
    return strcmp(nodeA->word, nodeB->word);
}
// 释放内存
void freeHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) 
    {
        WordNode *node = hashTable[i];
        while (node != NULL) 
        {
            WordNode *temp = node;
            node = node->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

void word_freq(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return;
    }
    printf("正在处理文件...\n");
    char line[MAX_LINE_LEN];
    int totalValidWords = 0;
    int lineNum = 0;
    // 万物之源-识别单词本来面目
    while (fgets(line, sizeof(line), file) != NULL) 
    {
        lineNum++;
        int lineLen = strlen(line);
        int start = -1; //不在单词中
        // 提取单词
        for (int i = 0; i <= lineLen; i++) 
        {
            char c = line[i];
            // 检查字母和撇号
            if (isalpha(c) || (c == '\'' && start != -1)) 
            {
                if (start == -1)  start = i; // 标记单词起始位置
            } 
            else 
            {
                if (start != -1)
                 {
                    char word[MAX_WORD_LEN] = {0};
                    int wordLen = 0;
                    // 提取单词
                    for (int j = start; j < i && wordLen < MAX_WORD_LEN - 1; j++) 
                    {
                        word[wordLen++] = tolower(line[j]);
                    }
                    word[wordLen] = '\0';
                    // 验证单词有效性
                    if (isValidWord(word, line, start, i)) 
                    {
                        insertWord(word);
                        totalValidWords++;
                    }
                    // 重置起始位置
                    start = -1;
                }
            }
        }
    }
    fclose(file);
    printf("处理完成！有效单词数: %d\n", totalValidWords);
    int wordCount = 0;
    WordNode **wordArray = collectWords(&wordCount);
    if (wordCount == 0) 
    {
        printf("未找到有效单词\n");
        freeHashTable();
        return;
    }
    printf("不同单词数: %d\n\n", wordCount);
    // 按字母顺序输出
    qsort(wordArray, wordCount, sizeof(WordNode *), compareAlpha);
    printf("===== 单词频率统计（按字母顺序）=====\n");
    printf("%-20s %-12s %s\n", "单词", "出现次数", "频率(%)");
    printf("------------------------------------------\n");
    
    for (int i = 0; i < wordCount; i++) 
    {
        float freq = totalValidWords > 0 ? 
                    (float)wordArray[i]->count / totalValidWords * 100 : 0;
        printf("%-20s %-12d %.2f%%\n", 
               wordArray[i]->word, 
               wordArray[i]->count, 
               freq);
    }
    free(wordArray);
    freeHashTable();
    printf("\n程序执行完毕。\n");
}