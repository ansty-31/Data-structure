#ifndef LINKSTNODE_H
#define LINKSTNODE_H

#include <stdio.h>
#include <malloc.h>
#include "btree.h"

typedef BTNode* ElemType;

typedef struct linknode
{
    ElemType data;  
    struct linknode *next;
} LinkStnode;

void InitStack(LinkStnode *&s);
void DestroyStack(LinkStnode *&s);
bool StackEmpty(LinkStnode *s);
void Push(LinkStnode *&s, ElemType e);
bool Pop(LinkStnode *&s, ElemType &e);
bool GetTop(LinkStnode *s, ElemType &e);

#endif