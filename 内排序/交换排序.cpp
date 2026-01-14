#include <stdio.h>
#include <malloc.h>


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

//冒泡排序 n、n^2、n^2，1（最好的、平均的、最坏的，空间）
void BubbleSort(RecType R[],int n)   //改进版，有时候第i（i<n-1）躺就已经拍好了，避免重复比较
{
    int i, j;
    bool exchange;
    for(i=0;i<n-1;i++)
    {
        exchange = false;
        for(j=n-1;j>i;j--)
        {
            if(R[j].key<R[j-1].key) swap(R[j],R[j-1]);
            exchange = true;
        }
        if(!exchange) return;
    }
}

//快速排序，划分成两个区域后，继续在各自区域划分（递归），nlogn,nlogn,n^2,logn,不稳定
int partition(RecType R[],int s,int t)
{
    int i=s,j=t;
    RecType tmp=R[i];
    while (i<j)
    {
        while (j>i&&R[j].key>=tmp.key)
        {
            j--;
        }
        R[i]=R[j];
        while (i<j&&R[i].key<=tmp.key)
        {
            i++;
        }
        R[j]=R[i];
    }
    R[i]=tmp;
    return i;
}
void QuickSort(RecType R[],int s,int t)
{
    int i;
    if(s<t)
    {
        i=partition(R,s,t);
        QuickSort(R,s,i-1);
        QuickSort(R,i+1,t);
    }
}
