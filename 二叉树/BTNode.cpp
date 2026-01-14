#include <stdio.h>
#include <malloc.h>

#define MaxSize 500
typedef ElemType char;

typedef struct node
{
    ElemType data;
    struct node *lchild;
    struct node *rchild;
}BTNode;

//顺序栈构建二叉树 A(B(C,D),E)
void CreateBTree(BTNode *&b, char *str)
{
    BTNode *St[MaxSize],*p;
    int top=-1,k,j=0;
    char ch;
    b=NULL;
    ch=str[j];
    while(ch!='\0')
    {
        switch (ch)
        {
        case '(':top++;St[top]=p;k=1;break; //k=1,处理左孩子
        case ')':top--;break;
        case ',':k=2;break;  //k=2,处理右孩子
        default:p=(BTNode *)malloc(sizeof(BTNode));
                p->data=ch;
                p->lchild=p->rchild=NULL;
                if(b==NULL)
                {
                    b=p;
                }
                else
                {
                    switch (k)
                    case '1':St[top]->lchild=p;break;
                    case '2':St[top]->rchild=p;break;
                }
        }
        j++;
        ch=str[j];
    }
}

void DestoryBTree(BTNode *&b)
{
    if(b!=NULL)
    {
        DestoryBTree(b->lchild);
        DestoryBTree(b->rchild);
        free(b);
    }
}

BTNode *FindNode(BTNode *b, ElemType x)
{
    if(b==NULL) return NULL;
    else if(b->data==x) return b;
    else 
    {
        BTNode *p;
        p=FindNode(b->lchild,x);
        if(p!=NULL) return p;
        else return FindNode(b->rchild,x);
    }
}

BTNode *LchildNode(BTNode *p)
{
    return p->lchild;
}
BTNode *RchildNode(BTNode *p)
{
    return p->rchild;
}

int BTHelight(BTNode *b)
{
    if (b==NULL) return 0;
    else
    {
        int lchildh,rchildh;
        lchildh=BTHelight(b->lchild);
        rchildh=BTHelight(b->rchild);
        return (lchildh>rchildh)?(lchildh+1):(rchildh+1);
    }
}

void DispBTree(BTNode *b)
{
    if(b!=NULL)
    {
        printf("%c",b->data);
        if(b->lchild!=NULL || b->rchild!=NULL)
        {
            printf("(");
            DispBTree(b->lchild);
            if(b->rchild!=NULL) printf(",");
            DispBTree(b->rchild);
            printf(")");
        }
    }
}

//二叉树的遍历（重点）
void PreOrder(BTNode *b)
{
    if(b!=NULL)
    {
        printf("%c",b->data);
        PreOrder(b->lchild);
        PreOrder(b->rchild);
    }
}
void InOrder(BTNode *b)
{
    if(b!=NULL)
    {
        InOrder(b->lchild);
        printf("%c",b->data);
        InOrder(b->rchild);
    }
}
void PostOrder(BTNode *b)
{
    if(b!=NULL)
    {
        PostOrder(b->lchild);
        PostOrder(b->rchild);
        printf("%c",b->data);
    }
}

/*层次遍历(队列，先访问的结点，到下一层时，他们的孩子也先访问)
typedef struct
{
    BTNode *data[MaxSize];
    int front,rear;
}sq_queue;

void LevelOrder(BTNode *b)
{
    BTNode *p;
    sq_queue *qu;
    init_queue(qu);
    en_queue(qu,b);
    while(!queue_empty(qu))  //环形队列，空间利用率高！
    {
        de_queue(qu,p)
        printf("%c",p->data);
        if(p->lchild!=NULL)
        {
            en_queue(qu,p->lchild);
        }
        if(p->rchild!=NULL)
        {
            en_queue(qu,p->rchild);
        }
    }
    destory_queue(qu);       
}*/

//递归构造二叉树
BTNode *CreateBT1(char *pre,char *in,int n)
{
    BTNode *b;
    char *p;
    int k;
    if(n<=0) return NULL;
    b=(BTNode*)malloc(sizeof(BTNode));
    b->data=*pre;
    for(p=in;p<in+n;p++)
    {
        if(*p==*pre) break;
    }
    k=p-in;
    b->lchild=CreateBT1(pre+1,in,k);
    b->rchild=CreateBT1(pre+k+1,p+1,n-k-1);
} //前序加中序，递归构造二叉树

BTNode *CreateBT2(char *post,char *in,int n)
{
    BTNode *b;
    char r,*p;
    int k;
    if(n<=0) return NULL;
    r=*(post+n-1);
    b=(BTNode*)malloc(sizeof(BTNode));
    b->data=r;
    for(p=in;p<in+n;p++)
    {
        if(*p==r) break;
    }
    k=p-in;
    b->lchild=CreateBT1(post,in,k);
    b->rchild=CreateBT1(post+k,p+1,n-k-1);
} //后序加中序，递归构造二叉树

