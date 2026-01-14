#include "..\linknode.cpp"

//  将链表按值x划分为两部分，<=x的结点在前，>x的结点在后
void split_list( LinkNode * L, ElemType x) 
{
    LinkNode *r,*p=L->next,*q;
    L->next=NULL;
    r=L;
    while(p!=NULL)
    {
        q=p->next;
        if(p->data<=x)
        {
            p->next=L->next;
            L->next=p;
            if (r==L)
            {
                r=p;
            }
        }
        else
        {
            if(p->data==x)
            {
                LinkNode *s=L;
                while (s!=NULL&&s->next->data<x)
                {
                    s=s->next;
                }
                p->next=s->next;
                s->next=p;
            } 
            else
            {
                p->next=NULL;
                r->next=p;
                r=p;
            }
            
        }
        p=q;
    }
}
