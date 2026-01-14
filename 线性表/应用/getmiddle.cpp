#include "..\linknode.cpp"


bool getMiddle(LinkNode *L, ElemType &e)
{
    LinkNode *p=L->next, *q=L->next;    //p�ǿ�ָ�룬q����ָ��
    if (L->next==NULL) return false; 
    while(p->next!=NULL)
    {
        p=p->next->next;
        q=q->next;
        if (p==NULL) return false;
    }
    e=q->data;
    return true;
}

int main()
{
    LinkNode *L;
    ElemType e=0;
    ElemType a[0];
    ElemType b[6]={1,2,3,4,5,6};
    ElemType c[5]={1,2,3,4,5};    //���������
    InitList(L);
    CreateListR (L,a,0);
    if (getMiddle(L,e))
    {
        printf("test1:%d\n",e);
    }
    else
    {
        printf("test1���м���\n");
    }
    DestroyList(L);

    InitList(L);
    CreateListR (L,b,6);
    if (getMiddle(L,e))
    {
        printf("test2:%d\n",e);
    }
    else
    {
        printf("test2���м���\n");
    }
    DestroyList(L);

    InitList(L);
    CreateListR (L,c,5);
    if (getMiddle(L,e))
    {
        printf("test3:%d\n",e);
    }
    else
    {
        printf("test3���м���\n");
    }
    DestroyList(L);
    return 0;
}

