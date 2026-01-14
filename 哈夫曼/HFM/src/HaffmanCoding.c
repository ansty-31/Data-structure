#include "Haffman.h"

// 最小堆相关操作
MinHeap *create_heap(int cap) // 创建最小堆
{
    MinHeap *h = (MinHeap *)malloc(sizeof(MinHeap));
    h->data = (HeapNode **)malloc(sizeof(HeapNode *) * cap);
    h->size = 0;
    h->cap  = cap;
    return h;
}

void swap_node(HeapNode **a, HeapNode **b) // 交换堆节点指针
{
    HeapNode *t = *a;
    *a = *b;
    *b = t;
}

void heapify_down(MinHeap *h, int i) // 堆下滤
{
    int l, r, smallest;
    while (1) {
        l = 2 * i + 1;
        r = 2 * i + 2;
        smallest = i;
        if (l < h->size && h->data[l]->freq < h->data[smallest]->freq)
            smallest = l;
        if (r < h->size && h->data[r]->freq < h->data[smallest]->freq)
            smallest = r;
        if (smallest == i) break;
        swap_node(&h->data[i], &h->data[smallest]);
        i = smallest;
    }
}

void heap_push(MinHeap *h, HeapNode *node)  // 堆入栈
{
    int i = h->size++;
    h->data[i] = node;
    while (i > 0 && h->data[(i - 1) / 2]->freq > h->data[i]->freq) {
        swap_node(&h->data[i], &h->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HeapNode *heap_pop(MinHeap *h) // 堆出栈
{
    HeapNode *root = h->data[0];
    h->data[0] = h->data[--h->size];
    heapify_down(h, 0);
    return root;
}

// 构建哈夫曼树
HeapNode *build_tree(const int count[MAX_CHARS]) 
{
    MinHeap *h = create_heap(MAX_CHARS);
    int i;
    // 插入所有非零频度字符节点
    for (i = 0; i < MAX_CHARS; ++i) 
	{
        if (count[i] > 0) 
		{
            HeapNode *node = (HeapNode *)malloc(sizeof(HeapNode));
            node->ch   = i;
            node->freq = (double)count[i];
            node->left = node->right = NULL;
            heap_push(h, node);
        }
    }
    // 处理特殊情况：空文件
    if (h->size == 0) 
	{
        free(h->data);
        free(h);
        return NULL;
    }
    // 构建哈夫曼树
    while (h->size > 1) 
	{
        HeapNode *a = heap_pop(h); 
        HeapNode *b = heap_pop(h); 
        HeapNode *parent = (HeapNode *)malloc(sizeof(HeapNode));
        parent->ch   = -1;
        parent->freq = a->freq + b->freq; 
        parent->left = a;
        parent->right = b;
        heap_push(h, parent);
    }
    HeapNode *root = heap_pop(h);
    free(h->data);
    free(h);
    return root;
}

// 生成哈夫曼编码表
void gen_codes(HeapNode *root, char *buf, int depth,
                      HuffmanCode *tbl, int *idx)
{
    if (root == NULL) return;
    // 叶子节点
    if (root->ch != -1) 
	{
        tbl[*idx].ch   = root->ch;
        tbl[*idx].freq = root->freq;
        buf[depth] = '\0';
        tbl[*idx].bits = (char *)malloc(depth + 1);
        strcpy(tbl[*idx].bits, buf);
        ++(*idx);
        return;
    }
    // 内部节点
    buf[depth] = '0';
    gen_codes(root->left,  buf, depth + 1, tbl, idx);
    buf[depth] = '1';
    gen_codes(root->right, buf, depth + 1, tbl, idx);
}

// 频度比较函数（降序）
int cmp_desc(const void *a, const void *b)
{
    double fa = ((const HuffmanCode *)a)->freq;
    double fb = ((const HuffmanCode *)b)->freq;
    if (fb > fa) return 1;
    if (fb < fa) return -1;
    return 0;
}

// 构建哈夫曼码表
HuffmanCode *build_huffman_table(const int count[MAX_CHARS], int *pSize)
{
    HeapNode *root = build_tree(count);
    HuffmanCode *table = NULL;
    int cap = 0, idx = 0;
    int i;
    // 处理空文件情况
    if (!root) 
	{ 
		*pSize = 0; return NULL; 
	}
    // 计算非零频度字符数量
    for (i = 0; i < MAX_CHARS; ++i)
    {
        if (count[i]) ++cap;
    }
    // 生成哈夫曼编码表    
    table = (HuffmanCode *)malloc(sizeof(HuffmanCode) * cap);
    {
        char buf[64];
        gen_codes(root, buf, 0, table, &idx);
    }
    *pSize = idx;
    // 排序哈夫曼码表（按频度降序）
    qsort(table, idx, sizeof(HuffmanCode), cmp_desc);
    return table;
}

// 输出哈夫曼码表
void output_huffman_table(const HuffmanCode *table, int size, int total)
{
    FILE *out = fopen("Statistic.txt", "a");  
    if (!out) {
        perror("无法打开 Statistic.txt");
        return;
    }

    fprintf(out, "\n================ 哈夫曼编码统计 ================\n");
    fprintf(out, "字符\tUnicode\t频度\t频率\t\t哈夫曼编码\n");
    fprintf(out, "-----------------------------------------------------------\n");

    int i;
    for (i = 0; i < size; ++i) {
        int ch = table[i].ch;
        char mb[8] = {0};
        wctomb(mb, (wchar_t)ch);

        double freq = table[i].freq / total;

        if (ch == L' ')
            fprintf(out, "'空格符'\tU+%04X\t%d\t%.6f\t%s\n",
                    ch, (int)table[i].freq, freq, table[i].bits);
        else if (ch == L'\n')
            fprintf(out, "'换行符'\tU+000A\t%d\t%.6f\t%s\n",
                    (int)table[i].freq, freq, table[i].bits);
        else if (ch == L'\r')
            fprintf(out, "'回车符'\tU+000D\t%d\t%.6f\t%s\n",
                    (int)table[i].freq, freq, table[i].bits);
        else if (ch == L'\t')
            fprintf(out, "'制表符'\tU+0009\t%d\t%.6f\t%s\n",
                    (int)table[i].freq, freq, table[i].bits);
        else
            fprintf(out, "%-6s\tU+%04X\t%d\t%.6f\t%s\n",
                    mb, ch, (int)table[i].freq, freq, table[i].bits);
    }
    fclose(out);
}

// 释放哈夫曼码表内存
void free_huffman_table(HuffmanCode *table, int size)
{
    int i;
    if (!table)  return;
    for (i = 0; i < size; ++i)
        free(table[i].bits);
    free(table);
}

//生成哈夫曼编码比特串
const char *get_huffman_bits(int ch, HuffmanCode *table, int size)
{int i = 0; 
    for (; i < size; ++i)
        if (table[i].ch == ch)
            return table[i].bits;
    return NULL;
}

// 输出哈夫曼编码比特流文件
int output_huffman_bitstream(const char *src, const char *dest, HuffmanCode *table, int size)
{
    setlocale(LC_ALL, "zh_CN.UTF-8");

    FILE *in  = fopen(src,  "r, ccs=UTF-8");
    FILE *out = fopen(dest, "wb");
    if (!in || !out) 
	{
        perror("文件打开失败");
        return -1;
    }

    unsigned char byte = 0;
    int bit_count = 0;
    // 读取源文件字符，转换为哈夫曼编码比特流
    wint_t ch;
    while ((ch = fgetwc(in)) != WEOF) 
	{
        const char *bits = get_huffman_bits(ch, table, size);
        if (!bits) continue;
		int i;
        for ( i = 0; bits[i]; ++i) 
		{
            byte <<= 1;
            if (bits[i] == '1')
                byte |= 1;

            bit_count++;

            if (bit_count == 8) {
            	
                fwrite(&byte, 1, 1, out);
                byte = 0;
                bit_count = 0;
            }
        }
    }
    // 处理剩余比特
    if (bit_count > 0) 
	{
        byte <<= (8 - bit_count);
        fwrite(&byte, 1, 1, out);
    }
    fclose(in);
    fclose(out);
    return 0;
}

