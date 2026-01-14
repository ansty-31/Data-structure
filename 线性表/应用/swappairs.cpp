#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct node {
   int data;
   node *next;
} LinkNode, *LinkList;

//insert link at the first location
void insert(LinkList & head, int data) {
   //create a link
   LinkNode *link = new LinkNode;
	
   link->data = data;
   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;
}

//display the list
void print(LinkList list) {
   LinkNode *ptr = list;
   printf("[ ");
	
   //start from the beginning
   while (ptr != NULL) {
      printf("%d ", ptr->data);
      ptr = ptr->next;
   }
	
   printf("]\n");
}

//学生答案放在这里 参照这个函数原型
LinkList swapPairs(LinkList list) {
      if(list==NULL||list->next==NULL)
      {
        return list;
      }
      else
      {
        LinkList pre=list;
        LinkList p=pre->next;
        LinkList rest=swapPairs(p->next);
        p->next=pre;
        pre->next=rest;
        return p; 
      }
}

int main()
{
    LinkList list = NULL;
    insert(list, 1); insert(list, 3); insert(list, 5);
    insert(list, 7); insert(list, 9); insert(list, 11);
    print(list);
    list = swapPairs(list);
    print(list);
}