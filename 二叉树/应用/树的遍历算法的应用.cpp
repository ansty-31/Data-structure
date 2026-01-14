#include "..\BTNode.cpp"

//确定所有结点个数
int Nodes(BTNode *b)
{
    if(b==NULL) return 0;
    else return Nodes(b->lchild)+Nodes(b->rchild)+1;
}

//输出所有叶子结点
void DispLeaf(BTNode *b)
{
    if(b!=NULL)
    {
        if(b->lchild==NULL&&b->rchild==NULL) printf("%c",b->data);
        DispLeaf(b->lchild);
        DispLeaf(b->rchild);
    }
}

//确定结点值为x的结点层次
int Level(BTNode *b,ElemType x,int h) //h初值为1
{
    if(b==NULL) return 0;
    else if(b->data==x) return h;
    else
    {
        l=Level(b->lchild,x,h+1); //这就是为什么要设置h（√）
        if(l!=0) return l;
        else return(Level(b->rchild,h+1));
    }
}

//确定k层的结点个数
void Lnodenum(BTNode *b, int h, int k, int &n)
{
    if(b==NULL) return 0;
    else
    {
        if(h==k) n++;
        else if(h<k)
        {
            Lnodenum(b->lchild,h+1,k,n);  //这就是为什么要设置n，或者也可以设为全局变量（上同理）
            Lnodenum(b->rchild,h+1,k,n);
        }
    }
}

//判断两个二叉树是否相似
bool Like(BTNode *b1, BTNode*b2)
{
    bool like1 ,like2; //1 is the left tree and 2 is the right tree
    if(b1==NULL&&b2==NULL) return true;
    else if(b1==NULL || b2==NULL) return false;
    else
    {
        like1=Like(b1->lchild,b2->rchild);
        like2=Like(b1->lchild,b2->rchild);
        return (like1&&like2);
    }
}

//输出值为x的所有祖先
bool ancestor(BTNode *b,ElemType x)
{
    if(b==NULL) return false;
    else if(b->lchild!=NULL&&b->lchild->data==x || b->rchild!=NULL&&b->rchild->data==x)
    {
        printf("%c",b->data);
        return true;  //这就是为什么设置bool，方便递归
    }
    else if(ancestor (b->lchild,x)||ancestor (b->rchild,x))
    {
        printf("%c",b->data);  //所有祖先
        return true;
    }
    else return false;
}