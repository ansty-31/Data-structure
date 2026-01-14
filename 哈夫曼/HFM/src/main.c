#include "Frequency.h"
#include "Haffman.h" 
#include "word_freq.h"
#include "search.h"

int main()
{
    setlocale(LC_ALL, "zh_CN.UTF-8");

    int count[MAX_CHARS];
    int total = 0;

    /* 1. 统计频度 */
    FILE *fp = fopen("SourceDoc.txt", "r, ccs=UTF-8");
    count_char_freq(fp, count, &total);
    fclose(fp);
 	print_freq(count, total); 
    /* 2. 构建哈夫曼码表 */
    int size;
    HuffmanCode *table = build_huffman_table(count, &size);
	output_huffman_table(table, size, total);
    /* 3. 编码 */
    output_huffman_bitstream("SourceDoc.txt", "Encode.dat", table, size);
	
    /* 4. 解码 */
    HeapNode *tree = rebuild_huffman_tree(count);
    huffman_decode_file("Encode.dat", "DecodeDoc.txt", tree);
    
    /* 5. 简单比对 */
    printf("\n=== 文件比对 ===\n");
    int is_match = compare_files_simple("SourceDoc.txt", "DecodeDoc.txt");
    printf("匹配结果: %s\n", is_match ? "成功" : "失败");

    /* 6. 扩展功能 */
    word_freq("SourceDoc.txt");
    search("SourceDoc.txt");

    free_huffman_table(table, size);
    return 0;
}



