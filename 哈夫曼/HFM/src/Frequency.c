#include "Frequency.h"

// 统计字符频度
int count_char_freq(FILE *fp, int count[MAX_CHARS], int *total)
{	
	int i = 0;
    // 初始化计数数组
    for (; i < MAX_CHARS; ++i) 
		count[i] = 0;
    *total = 0;
    // 读取文件并统计字符频度
    wint_t ch;
    while ((ch = fgetwc(fp)) != WEOF) 
	{
        if (ch >= 0 && ch < MAX_CHARS) 
		{
            count[ch]++;
            (*total)++;
        }
    }
    // 返回错误状态
    return ferror(fp) ? -1 : 0;
}

// 输出频度统计结果
void print_freq(const int count[MAX_CHARS], int total)
{
    if (total == 0) 
	{
        printf("无信息或未成功统计\n");
        return;
    }

    FILE *out = fopen("Statistic.txt", "w");
    if (!out) 
	{
        perror("无法打开 Statistic.txt");
        return;
    }
    
    Stat stats[MAX_CHARS];
    int n = 0;

    // 组装统计信息数组
    int i;
    for (i = 0; i < MAX_CHARS; ++i) 
	{
        if (count[i] > 0) 
		{
            stats[n].ch = i; 
            stats[n].cnt = count[i];
            stats[n].freq = (double)count[i] / total;
            n++;
        }
    }

    // 按频度降序排序（直接调用stdlib.h 中的快排函数）
    qsort(stats, n, sizeof(Stat), cmp_stat_desc);

    // 输出表头
    fprintf(out, "字符总数%d\n\n", total);
    fprintf(out, "字符\tUnicode\t次数\t频度\n");
    fprintf(out, "--------------------------------------------\n");

    // 输出统计结果
    for (i = 0; i < n; ++i) 
	{
        int ch = stats[i].ch;
        char mb[8] = {0};  
        wctomb(mb, (wchar_t)ch); // 宽字符转多字节字符

        if (ch == L' ')
            fprintf(out, "'空格符'\tU+%04X\t%d\t%.6f\n",
                    ch, stats[i].cnt, stats[i].freq);
        else if (ch == L'\n')
            fprintf(out, "'换行符'\tU+000A\t%d\t%.6f\n",
                    stats[i].cnt, stats[i].freq);
        else if (ch == L'\r')
            fprintf(out, "'回车符'\tU+000D\t%d\t%.6f\n",
                    stats[i].cnt, stats[i].freq);
        else if (ch == L'\t')
            fprintf(out, "'制表符'\tU+0009\t%d\t%.6f\n",
                    stats[i].cnt, stats[i].freq);
        else
            fprintf(out, "%-6s\tU+%04X\t%d\t%.6f\n",
                    mb, ch, stats[i].cnt, stats[i].freq); 
    }

    fclose(out);
}

// 频度比较函数
int cmp_stat_desc(const void *a, const void *b)
{
    double fa = ((const Stat *)a)->freq;
    double fb = ((const Stat *)b)->freq;
    if (fb > fa) return 1; 
    if (fb < fa) return -1; 
    return 0; 
}

