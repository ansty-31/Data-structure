#include "..\linknode.cpp"

void split(LinkNode* L, LinkNode*& L1, LinkNode*& L2)
{
    LinkNode *p = L->next, *q, *r1;
    L1 = L;
    r1 = L1;
    L2 =(LinkNode*)malloc(sizeof(LinkNode));
    L2->next = NULL;
    while (p!=NULL)
    {
        r1->next = p;
        r1 = p;  //尾插法
        p = p->next;
        if (p!=NULL)
        {
            q = p->next; //暂存下一个结点
            p->next = L2->next;
            L2->next = p;   //头插法
            p = q;  //继续处理下一个结点
        }
    }
    r1->next = NULL; //L1表尾结点next置NULL
}

void sort(LinkNode *&L)
{
    LinkNode *p, *pre, *q;
    p = L->next->next;;
    L->next->next = NULL;
    while (p!=NULL)
    {
        q = p->next; //暂存下一个结点
        pre = L; //从表头开始查找插入位置
        while (pre->next!=NULL && pre->next->data < p->data)
        {
            pre = pre->next;
        }
        p->next = pre->next;
        pre->next = p; //尾插进去
        p = q; //处理下一个结点
    }
} //还有双链表的，除了在尾插的时候处理前驱结点外，其他都一样