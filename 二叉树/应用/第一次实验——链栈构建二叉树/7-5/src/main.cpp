#include <iostream>
#include <stdio.h>
#include "../include/btree.h"
#include "../include/linkstnode.h"
#include "../include/expretree.h" 

int main()
{
  printf("---链栈测试开始---\n");
  LinkStnode *s;
  InitStack(s);
  printf("初始化链栈\n");
  printf("链栈初始化是否成功?: %s\n", StackEmpty(s) ? "是" : "否");
  BTNode node1 = {'A', NULL, NULL};
  BTNode node2 = {'B', NULL, NULL};
  Push(s, &node1);
  Push(s, &node2);
  printf("AB依次进入链栈\n");
  ElemType topElem;
  if (GetTop(s, topElem)) {
    printf("栈顶元素:  %c\n", topElem->data);
  }
  ElemType popElem;
  if (Pop(s, popElem)) {
    printf("出栈元素: %c\n", popElem->data);
  }
  if (GetTop(s, topElem)) {
    printf("更新栈顶元素:  %c\n", topElem->data);
  }
  printf("链栈是否为空?: %s\n", StackEmpty(s) ? "是" : "否");
  DestroyStack(s);
  printf("链栈已被销毁\n");

  printf("---二叉树测试开始---\n");
  BTNode *b,*p,*pleft,*pright;
  printf("请输入:");
  b=CreateBTree();
  printf("b: "); DispBTree(b); printf("\n");
  printf("b的高度: %d\n",BTHeight(b));
  p = FindNode(b,'B');
  if (p!=NULL) printf("b中有结点B\n");
  else printf("b中没有结点B\n");
  if (p!=NULL)
  {
    pleft=LchildNode(p);
    if (pleft!=NULL) printf("结点B的左孩子是 %c\n",pleft->data);
    else printf("结点B没有左孩子\n");
    pright=RchildNode(p);
    if (pright!=NULL) printf("结点B的右孩子是 %c\n",pright->data);
    else printf("结点B没有右孩子\n");
  }
  DestroyBTree(b);
  printf("二叉树已被销毁\n");
  printf("表达式请输入：");
  char expr[100];
  scanf("%s", expr);
  BTNode* root = CreateExprTree(expr);  
  if (root) {
    DispBTree(root);
    double result = EvaluateExprTree(root);
    printf("结果: %.2f\n", result);
    DestroyBTree(root);
  }
  return 0;
}
//g++ src/*.cpp -I include -o output/main.exe && .\output\main.exe
