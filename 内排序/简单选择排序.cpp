#include <stdio.h>

typedef int KeyType;
typedef char InfoType;

typedef struct
{
    KeyType key;     //关键字
    InfoType data;   //数据项
}RecType;   //每个数据元素的定义

void swap(RecType &R,RecType &R1)
{
    RecType tmp=R;
    R=R1;
    R1=tmp;
}

//简单选择排序，移动次数较少，但是n^2、n^2、n^2，还不稳定
void SelectSort(RecType R[],int n)
{
    int i,j,k;
    for(i=0;i<n;i++)
    {
        k=i;
        for(j=i+1;j<n;j++)
        {
            if(R[j].key<R[k].key) k=j;
        }
        if(k!=i) swap(R[i],R[k]);
    }
}