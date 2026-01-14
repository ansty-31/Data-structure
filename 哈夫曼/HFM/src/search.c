#include "search.h"

// 检查段落中是否包含任意一个目标字符串
int contains_any_string(const char *paragraph, char **targets, int target_count) 
{
    int i = 0;
    for (i = 0; i < target_count; i++) 
    {
        if (strstr(paragraph, targets[i]) != NULL)
        {
            return 1;  
        }
    }
    return 0; 
}

// 检查段落中是否包含所有目标字符串
int contains_all_strings(const char *paragraph, char **targets, int target_count) 
{
    int i = 0;
    for (i = 0; i < target_count; i++) 
    {
        if (strstr(paragraph, targets[i]) == NULL) 
        {
            return 0;  
        }
    }
    return 1;  
}

// 检查行是否为空行或切换段落
int is_empty_line(const char *line) 
{
    int i = 0;
    for (i = 0; line[i] != '\0'; i++) 
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r') 
        {
            return 0;  
        }
    }
    return 1;  
}

// 主搜索函数
void search(const char *filename) 
{
    // 设置中文环境
    setlocale(LC_ALL, "zh_CN.UTF-8");
    
    FILE *file;
    char input[MAX_LINE_LENGTH * MAX_TARGETS];  
    char *targets[MAX_TARGETS];  
    int target_count = 0;         
    char line[MAX_LINE_LENGTH];   
    int i;

    printf("请输入要搜索的字符串: "); // 多个字符串用空格隔开
    // 读取整行输入    
    if (fgets(input, sizeof(input), stdin) == NULL) 
    {
        printf("读取输入失败\n");
        return;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') 
    {
        input[len-1] = '\0';
    }
    
    // 分割输入字符串到目标数组
    char *token = strtok(input, " ");
    while (token != NULL && target_count < MAX_TARGETS) 
    {
        // 分配内存并复制字符串
        targets[target_count] = malloc(strlen(token) + 1);
        if (targets[target_count] == NULL) // 内存分配失败
        {
            fprintf(stderr, "内存分配失败\n");
            // 释放已分配的内存
            for (i = 0; i < target_count; i++) 
            {
                free(targets[i]);
            }
            return;
        }
        strcpy(targets[target_count], token);
        target_count++;
        token = strtok(NULL, " ");
    }
    
    // 检查是否有输入目标字符串
    if (target_count == 0) 
    {
        printf("未输入要搜索的字符串\n");
        return;
    }
    
    // 显示输入的目标字符串
    printf("搜索目标: "); 
    for (i = 0; i < target_count; i++) 
    {
        printf("'%s' ", targets[i]);
    }
    printf("\n");
    
    // 选择搜索模式
    printf("请选择搜索模式\n");
    printf("1. 匹配任意一个目标字符串的模式\n");
    printf("2. 匹配所有目标字符串的模式\n");
    printf("选择模式 (1/2): ");
    int mode;
    scanf("%d", &mode);
    getchar();  
    
    file = fopen(filename, "r");
    if (file == NULL) 
    {
        // 尝试UTF-8编码格式打开文件
        file = fopen(filename, "r, ccs=UTF-8");
        if (file == NULL) 
        {
            perror("无法打开文件");
            // 释放已分配的内存        
            for (i = 0; i < target_count; i++) 
            {
                free(targets[i]);
            }
            return;
        }
    }
    
    printf("\n=== 开始搜索 ===\n");
    
    // 统计信息
    int line_count = 0;      // 行数
    int found_count = 0;     // 匹配到的行数
    
    // 逐行读取文件内容
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) 
    {        
        line[strcspn(line, "\n")] = '\0'; // 移除换行符
        line[strcspn(line, "\r")] = '\0';
        line_count++;                
        
        // 搜索模式判断是否打印该行
        int should_print = 0;
        if (mode == 1) 
        {
            should_print = contains_any_string(line, targets, target_count);
        } 
        else 
        {
            should_print = contains_all_strings(line, targets, target_count);
        }
        
        // 打印匹配行
        if (should_print) 
        {
            found_count++;
            printf("\n=== 匹配到第 %d 行 ===\n", line_count);
            // 判断是否为空行，显示空行
            if (is_empty_line(line)) 
            {
                printf("(空行)\n");
            } 
            else 
            {
                printf("%s\n", line);
            }
        }
    }
    
    fclose(file);
    
    // 显示统计结果
    printf("\n=== 搜索结果 ===\n");
    printf("总行数: %d\n", line_count);
    printf("匹配行数: %d\n", found_count);
    printf("搜索模式: %s\n", mode == 1 ? "匹配任意一个目标字符串" : "匹配所有目标字符串");
    
    // 未找到匹配行时的提示
    if (found_count == 0 && line_count > 0) 
    {
        printf("\n显示未找到匹配行，请检查以下几点:\n");
        printf("1. 关键字拼写是否正确大小写\n");
        printf("2. 文件编码格式是否为UTF-8\n");
        printf("3. 文件中确实没有这些关键字\n");
        
        // 显示文件前5行内容，供用户参考
        printf("\n文件前5行内容:\n");
        file = fopen(filename, "r");
        if (file != NULL) 
        {
            fseek(file, 0, SEEK_SET);  // 将文件指针回到开头
            int lines_to_show = 5;
            int current_line = 0;
            while (fgets(line, MAX_LINE_LENGTH, file) != NULL && current_line < lines_to_show) 
            {
                line[strcspn(line, "\n")] = '\0';
                line[strcspn(line, "\r")] = '\0';
                // 显示行号
                current_line++;
                printf("第%d行: ", current_line);
                // 判断是否为空行，显示空行
                if (is_empty_line(line)) 
                {
                    printf("(空行)\n");
                } else {
                    printf("%s\n", line);
                }
            }
            fclose(file);
        }
    }
    
    // 释放内存
    for (i = 0; i < target_count; i++) 
    {
        free(targets[i]);
    }
}
