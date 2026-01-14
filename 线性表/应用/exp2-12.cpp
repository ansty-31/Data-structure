#include "..\linknode.cpp"

// 2.1 将字符串转换为链表
void string2list( LinkNode * & L, char *s )
{
    LinkNode*a;
    L=(LinkNode*)malloc(sizeof(LinkNode));
    L->next=NULL;
    while (*s!=0)
    {
        a=(LinkNode*)malloc(sizeof(LinkNode));
        a->data=*s-'0';
        a->next=L->next;
        L->next=a;
        s++;
    }
}

// 2.2 将两个链表表示的数相加，结果存入第三个链表
void add2list( LinkNode * L1, LinkNode * L2, LinkNode * & L ) 
{
    LinkNode *p=L1->next,*q=L2->next,*s;
    L=(LinkNode*)malloc(sizeof(LinkNode));
    L->next=NULL;
    int d=0,e=0;
    while (p!=NULL||q!=NULL||d!=0)
    {
        int sum=d;
        if(p!=NULL)
        {
            sum+=p->data;
            p=p->next;
        }
        if(q!=NULL)
        {
            sum+=q->data;
            q=q->next;
        }
        e=sum%10;
        d=sum/10;
        s=(LinkNode*)malloc(sizeof(LinkNode));
        s->data=e;
        s->next=L->next;
        L->next=s;
    } 
}

// 2.3 返回链表的中间结点的值
int mid_list( LinkNode *  L )
{
    LinkNode *p=L->next, *q=L->next;    
    if (L->next==NULL) return 0; 
    while(p->next!=NULL)
    {
        p=p->next->next;
        q=q->next;
        if (p==NULL) break;
    }
    int e=q->data;
    return e;
}
