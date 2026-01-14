#include <stdio.h>
#include <malloc.h>

typedef int ElemType;

typedef struct linknode
{
    ElemType data;  
    struct linknode *next;
} LinkStnode;

void InitStack(LinkStnode *&s)
{
    s=(LinkStnode*)malloc(sizeof(LinkStnode));
    s->next=NULL;
}

void DestroyStack(LinkStnode *&s)
{
    LinkStnode *pre=s,*p=s->next;
    while (p!=NULL)
    {
        free(pre);
        pre=p;
        p=pre->next;
    }
    free(pre);
}

bool StackEmpty(LinkStnode *s)
{
    return(s->next==NULL);
}

void Push(LinkStnode *&s, ElemType e)
{
    LinkStnode *p;
    p=(LinkStnode*)malloc(sizeof(LinkStnode));
    p->data=e;
    p->next=s->next;
    s->next=p;
}

bool Pop(LinkStnode *&s,ElemType &e)
{
    LinkStnode *p;
    if(s->next==NULL) return false;
    p=s->next;
    e=p->data;
    s->next=p->next;
    free(p);
    return true;
}

bool GetTop(LinkStnode *s,ElemType &e)
{
    if(s->next==NULL) return false;
    e=s->next->data;
    return true;
}