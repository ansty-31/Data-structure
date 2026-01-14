#include <stdio.h>
#include <malloc.h>

typedef char ElemType;
typedef struct DNode
{
    ElemType data;
    struct DNode *prior;
    struct DNode *next;
}DLinkNode;

void CreateListF(DLinkNode *&L,ElemType a[],int n)
{
    DLinkNode *s;
    L=(DLinkNode*)malloc(sizeof(DLinkNode));
    L->prior=L->next=NULL;
    for(int i=0;i<n;i++)
    {
        s=(DLinkNode*)malloc(sizeof(DLinkNode));
        s->data=a[i];
        s->next=L->next;
        if (L->next!=NULL)
        {
            L->next->prior=s;
        }
        L->next=s;
        s->prior=L;
    }
}

void CreateListR(DLinkNode *&L,ElemType a[],int n)
{
    DLinkNode *s,*r;
    L=(DLinkNode*)malloc(sizeof(DLinkNode));
    r=L;
    for(int i=0;i<n;i++)
    {
        s=(DLinkNode*)malloc(sizeof(DLinkNode));
        s->data=a[i];
        r->next=s;
        s->prior=r;
        r=s;
    }
    r->next=NULL;
}

void InitList(DLinkNode *&L)
{
    L=(DLinkNode*)malloc(sizeof(DLinkNode));
    L->prior=L->next=NULL;
}

void DestroyList(DLinkNode *&L)
{
    DLinkNode *pre=L,*p=L->next;
    while(p!=NULL)
    {
        free(pre);
        pre=p;
        p=pre->next;
    }
    free(pre);
}

bool ListEmpty(DLinkNode *L)
{
    return(L->prior==L->next&&L->next==NULL);
}

int ListLength(DLinkNode *L)
{
    int n=0;
    DLinkNode *p=L;
    while (p->next!=NULL)
    {
        n++;
        p=p->next;
    }
    return n;
}

void DispList(DLinkNode *L)
{
    DLinkNode *p=L->next;
    while (p!=NULL)
    {
        printf("%c ",p->data);
        p=p->next;
    }
    printf("\n");
}

bool GetElem(DLinkNode *L,int i,ElemType &e)
{
    int j=0;
    DLinkNode *p=L;
    if(i<=0) return false;
    while (j<i&&p!=NULL)
    {
        j++;
        p=p->next;
    }
    if(p==NULL)
    {
        return false;
    }
    else
    {
        e=p->data;
        return true;
    }
}

int LocateElem(DLinkNode *L,ElemType e)
{
    int i=1;
    DLinkNode *p=L->next;
    while (p!=NULL&&p->data!=e)
    {
        i++;
        p=p->next;
    }
    if(p==NULL)
    {
        return 0;
    }
    else
    {
        return i;
    }
}

bool ListInsert(DLinkNode *&L,int i,ElemType e)
{
    int j=0;
    DLinkNode *p=L,*s;
    if(i<=0) return false;
    while (j<i-1&&p!=NULL)
    {
        j++;
        p=p->next;
    }
    if(p==NULL)
    {
        return false;
    }
    else
    {
        s=(DLinkNode*)malloc(sizeof(DLinkNode));
        s->data=e;
        s->next=p->next;
        if(p->next!=NULL)
        {
            p->next->prior=s;
        }
        p->next=s;
        s->prior=p;
        return true;
    }
}

bool ListDelete(DLinkNode *&L,int i,ElemType &e)
{
    int j=0;
    DLinkNode *p=L,*q;
    if(i<=0) return false;
    while (j<i-1&&p!=NULL)
    {
        j++;
        p=p->next;
    }
    if(p==NULL)
    {
        return false;
    }
    else
    {
        q=p->next;
        if(q==NULL) return false;
        e=q->data;
        p->next=q->next;
        if(q->next!=NULL)
        {
            q->next->prior=p;
        }
        free(q);
        return true;
    }
}