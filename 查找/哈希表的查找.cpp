#include <stdio.h>
#include <malloc.h>

//开发地址法构造的哈希表的运算函数
#define NULLKEY -1  //空闲单元的关键字值
#define DELKEY -2   //被删单元的关键字值
typedef int KeyType;
typedef struct 
{
    KeyType key;  
    int count;  //探测次数域
}HashTable;  //哈希表单元类型

//插入和创建
void InsertHT(HashTable ha[], int &n, int m, int p, KeyType k) //m是哈希表长度，p是小于等于m的最大素数
{
    int i, adr;
    adr=k%p;
    if(ha[adr].key==NULLKEY||ha[adr].key==DELKEY)
    {
        ha[adr].key=k;
        ha[adr].count=1;
    }
    else
    {
        while(ha[adr].key!=NULLKEY&&ha[adr].key!=DELKEY)
        {
            i++;
            adr=(adr+1)%m; //adr+1<=p<=m,这里是为了后移，为了能找到位置，对长度m求余
        }
        i++;
        ha[adr].key=k;
        ha[adr].count=i;
    }
    n++;  
}
void CreateHT(HashTable ha[], int &n, int m, int p, KeyType keys[],int n1)
{
    for(int i=0;i<m;i++)
    {
        ha[i].key=NULLKEY;
        ha[i].count=0;
    }
    n=0;   //记录哈希表中有效元素个数
    for(int i=0;i<n1;i++)
    {
        InsertHT(ha,n,m,p,keys[i]);
    }
}

//删除
bool DeleteHT(HashTable ha[], int &n, int m, int p, KeyType k)
{
    int adr;
    adr=k%p;
    whlie(ha[adr].key!=NULLKEY&&ha[adr].key!=k) adr=(adr+1)%m;  //k可能不在，也可能在
    if(ha[adr].key==k)
    {
        ha[adr].key=DeleteHT;
        n--;
        return true;
    }
    else return false;
}

//查找
void SearchHT(HashTable ha[], int m, int p, KeyType k)
{
    int i=1,adr;
    adr=k%p;
    whlie(ha[adr].key!=NULLKEY&&ha[adr].key!=k)
    {
        adr=(adr+1)%m;
        i++;
    }
    if(ha[adr].key==k)
    {
        printf("成功：关键字%d,比较%d次\n",k,i);
    }
    else
    {
        printf("失败：关键字%d,比较%d次\n",k,i);
    }
}

//查找性能分析，count在这里派上了用场
void ASL(HashTable ha[], int n, int m, int p)
{
    int i,j;
    int succ=0,unsucc=0,s;
    for(i=0;i<m;i++)
    {
        if(ha[i].key!=NULLKEY) succ+=ha[i].count;
    }
    printf("成功情况下ASL(%d)=%g\n",n, succ*1.0/n);
    for(i=0;i<m;i++)
    {
        s=1;j=i;
        while(ha[j].key!=NULLKEY)
        {
            s++;
            j=(j+1)%m; //确保j没有越界，而是在哈希表里从左向右遍历
        }
        unsucc+=s;
    }
    printf("不成功情况下ASL(%d)=%g\n",n,unsucc*1.0/p); //任取一个失败的数字%p，可以是p个值，故共p种结果
}


//拉链法构造的哈希表的运算函数(形式像邻接表)
typedef struct node
{
    KeyType key;
    struct node *next;
}NodeType;
typedef struct 
{
    NodeType *firstp;
}HashTable1; 

void insert_ht(HashTable1 ha[],int &n,int p,KeyType k)
{
    int adr;
    adr=k%p;
    NodeType *q;
    q=(NodeType)malloc(sizeof(NodeType));
    q->key=k;
    q->next=NULL;     //创建临时指针
    if(ha[adr].firstp==NULL)
    {
        ha[adr].firstp=q;
    }
    else
    {
        q->next=ha[adr].firstp;
        ha[adr].firstp=q;   //头插法
    }
    n++;
}
void CreateHT(HashTable1 ha[],int &n,int m,int p,KeyType keys[],int n1)
{
    for(int i=0;i<m;i++)
    {
        ha[i].firstp=NULL;
    }
    n=0;
    for(int i=0;i<n1;i++)
    {
        insert_ht(ha,n,p,keys[i]);
    }
}

bool delete_ht(HashTable1 ha[], int &n, int m, int p, KeyType k)
{
    int adr = k % p; 
    NodeType *q = ha[adr].firstp;
    NodeType *preq = NULL;
    while (q != NULL)
    {
        if (q->key == k)  
        {
            if (preq == NULL)  ha[adr].firstp = q->next;  //说明是首结点
            else  preq->next = q->next;
            free(q);
            n--;
            return true;
        }
        preq = q;
        q = q->next;
    }
    return false;  
}

void search_ht(HashTable1 ha[], int p, KeyType k)
{
    int i=0, adr=k%p;
    NodeType *q;
    q=ha[adr].firstp;
    while (q!=NULL)
    {
        i++;
        if(q->key==k) break;
        else q=q->next;
    }
    if(q!=NULL)
    {
        printf("成功：关键字%d,比较%d次\n",k,i);
    }
    else
    {
        printf("失败：关键字%d,比较%d次\n",k,i);
    }
}

void asl(HashTable1 ha[], int n, int m)
{
    int succ=0, unsucc=0,s;
    NodeType *q;
    for(int i=0;i<m;i++)
    {
        s=0;
        q=ha[i].firstp;
        while (q!=NULL)
        {
            q=q->next;
            s++;
            succ+=s;
        }
        unsucc+=s;  //不包括空指针判定
    }
    printf("成功情况下ASL(%d)=%g\n",n, succ*1.0/n);
    printf("不成功情况下ASL(%d)=%g\n",n, unsucc*1.0/n);
}