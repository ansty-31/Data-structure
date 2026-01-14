#include <stdio.h>

typedef int KeyType;
typedef char InfoType;


typedef struct 
{
    KeyType key;
    InfoType data;
}RecType;  //查找元素的类型

//顺序查找,ASL成功=(n+1)/2,ASL不成功=n
int SeqSearch(RecType R[], int n, KeyType k)
{
    int i=0;
    R[n].key=k;   //哨兵,如果i==n,说明出界了
    while (R[i].key!=k)
    {
        i++;
    }
    if(i==k) return 0;
    else return i+1;   //返回逻辑序号
}

//二分查找,利用判定树,易得ASL=log(n+1)-1,成功和不成功都极为接近,但是要求查找表必须是有序的
int BinSearch(RecType R[],int n, KeyType k)
{
    int low=0, high=n-1,mid;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(k==R[mid].key) return mid+1;
        if(k<R[mid].key) high=mid-1;
        else low = mid+1;
    }
    return 0;
}

//分块查找,"分快有序"+索引表,折半法的话ASL=log(n/s+1)+s/2,全程顺序法的话0.5(n/s+s)+1
typedef struct 
{
    KeyType key;
    int link;   //指向对应块的下标
}IdxType;
//分块查找先是在索引表里二分查找,然后定位到块里顺序查找,查找两次
int IdxSearch(IdxType I[], int b, RecType R[],int n, KeyType k)
{
    int s=(n+b-1)/b;  //每块的元素个数
    int low=0,high=b-1,mid,i;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(I[mid].key>=k) high=mid-1;
        else low = mid+1;
    }
    i=I[high+1].link;  //确定到的位置是high+1,因为多减了一次
    while(i<=I[high+1].link+s-1&&R[i].key!=k) i++;
    if(i<=I[high+1].link+s-1) return i+1;
    else return 0;
}

