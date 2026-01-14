#include <stdio.h>
#include <malloc.h>

#define MAXD 100  //关键字最大的位数可能

typedef struct
{
    char data[MAXD];     //关键字位数
    struct node *next;   //指向下一个结点
}NodeType;   //基数排序数据的结点类型

//基数排序，针对单链表的数据排序，d(n+r),d(n+r),d(n+r),r
void RadixSort(NodeType *&p, int r, int d) //r表示数据个数，d表示关键字最大位数
{
    NodeType *head[10],*tail[10],*t;    //t为单链表p的尾指针
    int i,j,k;
    for(i=0;i<=d-1;i++)
    {
        for(j=0;j<r;j++)
        {
            head[j]=tail[j]=NULL;
        }//初始化各链队的首尾指针
        while (p!=NULL)
        {
            k=p->data[i]-'0';
            if(head[k]==NULL)
            {
                head[k]=p;
                tail[k]=p;
            }
            else
            {
                tail[k]->next=p;
                tail[k]=p; //尾插法进链
            }
            p=p->next;
        }   //分配完一次
        p=NULL;
        for(j=0;j<r;j++)
        {
            if(head[j]!=NULL)
            {
                if(p==NULL)  //若j链队是第一个非空链队
                {
                    p=head[j];t=tail[j];
                }
                else
                {
                    t->next=head[j];t=tail[j];  //依旧尾插法,处理链队（保持原链表顺序）
                }
            }
        }
        t->next=NULL;
    }  

}