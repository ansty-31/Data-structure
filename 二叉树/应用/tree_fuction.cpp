#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

typedef char ElemType;
 
typedef struct _Node { //结点类，内部class
    ElemType data;           	//结点数据域
    struct _Node*  left; 	//结点左子树的指针
	struct _Node*  right; 	//结点右子树的指针
} Node, *BinaryTree;

void operator delete (void* m)
{
    Node *bn = (Node *)m;
    std::cout<<"X"<< bn->data << ") ";
    free(m);
}

static void visit(ElemType v) {
   cout << v << ' ';
} //访问

void  preorder(const Node * r) {
    if (r == NULL)
       return;
    visit(r->data);		//访问根结点
    preorder(r->left);
    preorder(r->right);
}

void postorder(const Node* r) {
    if (r == NULL) 
       return;
    postorder(r->left);
    postorder(r->right);
    visit(r->data);		//访问根结点
}

void  inorder(const  Node* r) {
    if (r == NULL) 
       return;
    inorder(r->left);
    visit(r->data);		//访问根结点
    inorder(r->right);
}

static Node * CreateNode(ElemType data ) {
	Node *r = new Node;
	r->data = data;
	r->left = NULL;
	r->right = NULL;
	return r;
}		

BinaryTree CreateTree() {
    ElemType ch;
    cin >> ch;
	Node *r;
    if (ch == '#')
        r = NULL;
    else {	  //读入非空符号
        r = CreateNode(ch);		//生成结点
        r->left = CreateTree();			//构造左子树
        r->right = CreateTree();			//构造右子树
    }
    return r;
}

//1 二叉树-销毁一棵树，按后序遍历把所有的结点销毁（delete）
// 对每个结点调用 delete，并置为空
static void cutTree( BinaryTree &r );

//2 二叉树-求树的深度
static int getHeight(const BinaryTree &r);
//3 二叉树--求某层的节点个数
static int getNodeNumberLK(const BinaryTree &r, int k);
//4 二叉树--根据前序、中序遍历创建一棵二叉树
void CreateTree2( BinaryTree &r, char * preorder, char *inorder);
//5 给定一个二叉树, 找到该树中两个指定结点的最近公共祖先
static Node * findCmnAn( BinaryTree &r, ElemType pe, ElemType qe);

static void cutTree( BinaryTree &r )
{
    if(r==NULL) return;
    cutTree(r->left);
    cutTree(r->right);
    delete(r);
    r=NULL;
}
static int getHeight(const BinaryTree &r)
{
    if(r==NULL) return 0;
    int leftheight=getHeight(r->left);
    int rightheight=getHeight(r->right);
    return (leftheight > rightheight ? leftheight : rightheight) + 1;
}
static int getNodeNumberLK(const BinaryTree &r, int k)
{
    if(r==NUL||k<1) return 0;
    if(k==1) return 1;
    return getNodeNumberLK(r->left,k-1)+getNodeNumberLK(r->right,k-1);
}
void CreateTree2( BinaryTree &r, char * preorder, char *inorder)
{
    if (preorder == NULL || *preorder == '\0' || inorder == NULL || *inorder == '\0')
    {
        r = NULL;
        return;
    }
    r=(Node*)malloc(sizeof(Node));
    r->data=*preorder;
    r->left=NULL;
    r->right=NULL;
    char *p=inorder;
    int k = 0;
    while (*p!='\0' && *p!= *preorder)
    {
        p++;
        k++;
    }
    if(*p=='\0') 
    {
        free(p);
        r=NULL;
        return;
    }
    char savedInChar = *p;           
    char savedPreChar = preorder[1 + k]; 
    *p = '\0';                       
    preorder[1 + k] = '\0'; 
    CreateTree2(r->left, preorder + 1, inorder);
    *p = savedInChar;
    preorder[1 + k] = savedPreChar;
    CreateTree2(r->right,preorder+1+k,p+1);
}
static Node * findCmnAn( BinaryTree &r, ElemType pe, ElemType qe)
{
    if(r==NULL||r->data==pe||r->data==qe)
    {
        return r;
    }
    Node *left=findCmnAn(r->left,pe,qe);
    Node *right=findCmnAn(r->right,pe,qe);
    if(left!=NULL&&right!=NULL)
    {
        return r;
    }
    return left != NULL ? left : right;
}

int main() {
    Node *r = CreateTree( );
    BinaryTree bt = r;
    cout << getHeight(bt) << '=' << getNodeNumberLK(bt, 3) << endl;
    postorder(bt);
    cout << endl;
    cutTree(bt->left);
    cout << endl;
    postorder(bt);
    return 0;
}