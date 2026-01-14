#include "../include/btree.h"
#include "../include/linkstnode.h"


BTNode* CreateBTree() {
    LinkStnode *st;
    BTNode *b = NULL, *p, *q;
    char str[100];
    int i = 0;
    InitStack(st);
    scanf("%s", str);
    
    while (str[i] != '\0') 
    {
        if (str[i] == '(') {
            Push(st, p);  
        }
        else if (str[i] == ',') {
        }
        else if (str[i] == ')') {
            Pop(st, p);
        }
        else if (str[i] != '#') {
            p = (BTNode*)malloc(sizeof(BTNode));
            p->data = str[i];
            p->lchild = p->rchild = NULL;
            if (b == NULL) {
                b = p;
            }
            else {
                ElemType parent;
                if (GetTop(st, parent)) {
                    if (parent->lchild == NULL) {
                        parent->lchild = p;
                    }
                    else {
                        parent->rchild = p;
                    }
                }
            }
        }
        i++;
    }    
    DestroyStack(st);
    return b;
}

void DestroyBTree(BTNode *&b)
{
    if (b==NULL) return ;
    else
    {
        DestroyBTree(b->lchild);
        DestroyBTree(b->rchild);
        free(b);     
    }
}

BTNode *FindNode(BTNode *b,char x) 
{
   if (b==NULL) return NULL;
   else if (b->data==x) return b;
   else
   {
       BTNode * p = FindNode(b->lchild,x);
       if (p!=NULL) return p;
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

int BTHeight(BTNode *b) 
{
   int lchilddep,rchilddep;
   if (b==NULL) return(0); 
   else  
   {
      lchilddep = BTHeight(b->lchild);	
      rchilddep = BTHeight(b->rchild);
      return (lchilddep>rchilddep)? (lchilddep+1):(rchilddep+1);
   }
}

void DispBTree(BTNode *b) 
{
   if (b!=NULL) {
      printf("%c",b->data);
      if (b->lchild!=NULL || b->rchild!=NULL) {
         printf("(");
	  DispBTree(b->lchild);
	  if (b->rchild!=NULL)
            printf(",");
	  DispBTree(b->rchild);
	  printf(")");
      }
   }
}





