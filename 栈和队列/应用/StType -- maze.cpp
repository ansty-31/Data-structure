#include <stdio.h>
#include <malloc.h>

#define MaxSize 100

typedef struct 
{
    int i;
    int j;
    int di;
}Box;

typedef struct 
{
    Box data[MaxSize];
    int top;
}StType;

void InitStack(StType *&S)
{
    S=(StType*)malloc(sizeof(StType));
    S->top=-1;
}

void DestroyStack(StType*&S)
{
    free(S);
}

bool StackEmpty(StType *S)
{
    return(S->top==-1);
}

bool Push(StType *&S,Box e)
{
    if(S->top==MaxSize-1) return false;
    S->top++;
    S->data[S->top]=e;
    return true;
}

bool Pop(StType *&S,Box &e)
{
    if(S->top==-1) return false;
    e=S->data[S->top];
    S->top--;
    return true;
}

bool GetTop(StType *S,Box &e)
{
    if(S->top==-1) return false;
    e=S->data[S->top];
    return true;
}

