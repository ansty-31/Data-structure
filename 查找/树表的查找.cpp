#include <stdio.h>
#include <malloc.h>

typedef int KeyType;
typedef char InfoType;

typedef struct node
{
    KeyType key;
    InfoType data;
    struct node *lchild, *rchild;
}BSTNode;

//二叉排序树的插入
bool InsertBST(BSTNode *&bt, KeyType k)
{
    if(bt==NULL)
    {
        bt=(BSTNode *)malloc(sizefo(BSTNode));
        bt->key=k;bt->lchild=bt->rchild=NULL;
        return true;
    }
    else if(k==bt->key) return false;  //记得不能重复出现关键字
    else if(k<bt->key)  return InsertBST(bt->lchild,k);
    else return InsertBST(bt->rchild,k);
}

//二叉排序树的创建
BSTNode *CreateBST(KeyType a[],int n)
{
    BSTNode *bt=NULL;  //初始时二叉树为空树,配合InsertBST
    for(int i=0;i<n;i++)
    {
        InsertBST(bt,a[i]);
    }
    return bt;
}

//二叉排序树的查找(log(n),相比折半法，时间性能差不多，但是二叉排序树，无须移动元素，改改指针就行)
BSTNode *SearchBST(BSTNode *bt, KeyType k)
{
    if(bt->key==k||bt==NULL) return bt;
    if(bt->key>k) return SearchBST(bt->lchild,k);
    else return SearchBST(bt->rchild,k);
}
//除了返回该结点，还可以返回其双亲结点(f用于返回其双亲结点，pref是中间参数，初始值为NULL)
BSTNode *SearchBST1(BSTNode *bt, KeyType k, BSTNode *pref, BSTNode *&f)
{
    if(bt==NULL)
    {
        f=NULL;
        return NULL;
    }
    else if(bt->key==k)
    {
        f=pref;
        return bt;
    }
    else if(bt->key>k) return SearchBST1(bt->lchild,k,bt,f);
    else return SearchBST1(bt->rchild,k,pref,f);
}

//二叉排序树的删除
void Deletel(BSTNode *&p, BSTNode *&r)  //用p左子树r中的最大值覆盖p，删除多余的r，再接上r的子树
{
    BSTNode *q;
    if(r->rchild!=NULL) Deletel(p,r->rchild);  //左子树中递归找到最大的结点
    else
    {
        p->key=r->key;
        p->data=r->data;
        q=r;
        r=r->lchild;
        free(q);
    }
}
void Delete(BSTNode *&p)
{
    BSTNode *q;
    if(p->rchild==NULL)   //只有左子树(含叶子结点)
    {
        q=p;
        p=p->lchild;
        free(q);
    }
    else if(p->lchild==NULL)  //只有右子树
    {
        q=p;
        p=p->rchild;
        free(q);
    }
    else Deletel(p,p->lchild);  //左右子树都有，采用取左子树中最大结点代替root
}
bool DeleteBST(BSTNode *&bt, KeyType k)
{
    if(bt==NULL) return false;
    else
    {
        if(bt->key==k)
        {
            Delete(bt);
            return true;
        }
        else if(bt->key>k) return DeleteBST(bt->lchild,k);
        else DeleteBST(bt->rchild,k);
    }
}

//关于平衡二叉树(每个结点的左右子树高度差不超过1的二叉排序树)，详细见树表的查找.md

//外查找：B_树和B+树的插入、删除和查找，详细见树表的查找.md
#define MAXM 10
typedef struct node
{
    int keynum;
    KeyType key[MAXM];
    struct node *parent;
    struct node *ptr[MAXM];
}BTNode;
int m;  //m阶B_树，所有结点的孩子结点的最大值
int Max; //每个结点的最多关键字MAX=m-1
int Min; //每个结点的最少关键字Min=(m+1)/2-1



