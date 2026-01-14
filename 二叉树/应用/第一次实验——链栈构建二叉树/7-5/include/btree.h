#ifndef BTREE_H
#define BTREE_H

typedef struct node
{
    char data;
    struct node* lchild;
    struct node* rchild;
}BTNode;


BTNode* CreateBTree();
void DestroyBTree(BTNode *&b);
BTNode *FindNode(BTNode *b, char x);  
BTNode *LchildNode(BTNode *p);
BTNode *RchildNode(BTNode *p);
int BTHeight(BTNode *b);
void DispBTree(BTNode *b);

#endif