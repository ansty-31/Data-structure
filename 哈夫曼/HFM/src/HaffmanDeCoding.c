#include "Haffman.h"

//重建哈夫曼树
HeapNode *rebuild_huffman_tree(const int count[MAX_CHARS])
{
    MinHeap *h = create_heap(MAX_CHARS);
	int i = 0;
    // 插入所有非零频度字符节点
    for (; i < MAX_CHARS; ++i) 
	{
        if (count[i] > 0) 
		{
            HeapNode *node = (HeapNode *)malloc(sizeof(HeapNode));
            node->ch = i;
            node->freq = count[i];
            node->left = node->right = NULL;
            heap_push(h, node);
        }
    }
    // 处理特殊情况：空文件
    if (h->size == 0) return NULL;
    // 构建哈夫曼树
    while (h->size > 1) 
	{
        HeapNode *a = heap_pop(h);
        HeapNode *b = heap_pop(h);
        HeapNode *parent = (HeapNode *)malloc(sizeof(HeapNode));
        parent->ch = -1;
        parent->freq = a->freq + b->freq;
        parent->left = a;
        parent->right = b;
        heap_push(h, parent);
    }
    return heap_pop(h);
}

// 哈夫曼解码生成文档
int huffman_decode_file(const char *bin, const char *out, HeapNode *tree)
{
    setlocale(LC_ALL, "zh_CN.UTF-8");

    FILE *in = fopen(bin, "rb");
    FILE *fp = fopen(out, "w, ccs=UTF-8");  // 输出为UTF-8编码
    if (!in || !fp) 
	{
        perror("打开文件失败");
        return -1;
    }

    HeapNode *cur = tree;
    unsigned char byte;
    // 读取比特流并解码
    while (fread(&byte, 1, 1, in) == 1) 
	{
	int i = 7;
        for (; i >= 0; --i) 
		{
            int bit = (byte >> i) & 1;//提取当前比特
            cur = bit ? cur->right : cur->left;
            // 检查是否到达叶子节点
            if (!cur) 
            {
                fclose(in);
                fclose(fp);
                return -1;
            }
            // 到达叶子节点
            if (cur->ch != -1) 
			{
                fputwc((wchar_t)cur->ch, fp);//写入解码字符
                cur = tree;
            }
        }
    }
    fclose(in);
    fclose(fp);
    return 0;
}

// 简单文件比对
int compare_files_simple(const char* file1_path, const char* file2_path) 
{
    FILE* fp1 = fopen(file1_path, "r, ccs=UTF-8");
    FILE* fp2 = fopen(file2_path, "r, ccs=UTF-8");
    
    if (!fp1 || !fp2) 
	{
        if (fp1) fclose(fp1);
        if (fp2) fclose(fp2);
        printf("无法打开文件\n");
        return 0;
    }
    
    wint_t c1, c2;
    int total = 0;
    int matched = 0;
    
    while (1) 
	{
        c1 = fgetwc(fp1);
        c2 = fgetwc(fp2);
        if (c1 == WEOF && c2 == WEOF) 
		{
            break; // 文件同时结束
        }
        total++;
        if (c1 == c2) 
		{
            matched++;
        } 
		else 
		{
            fclose(fp1);
            fclose(fp2);
            printf("文件不一致。比较了 %d 个字符，匹配了 %d 个 (%.2f%%)\n", 
                   total, matched, (float)matched/total*100);
            return 0;
        }
    }
    fclose(fp1);
    fclose(fp2);
    printf("文件完全一致。比较了 %d 个字符，全部匹配\n", total);
    return 1;
}

