#include <stdio.h>
#include <malloc.h>

#define MaxSize 100
typedef char ElemType;
typedef struct 
{
    ElemType data[MaxSize];   
    int top;   //栈顶元素在data数组中的下标
}SqStack;

void InitStack(SqStack *&S)
{
    S=(SqStack*)malloc(sizeof(SqStack));
    S->top=-1;
}

void DestroyStack(SqStack *&S)
{
    free(S);
}

bool StackEmpty(SqStack *S)
{
    return(S->top==-1);
}

bool Push(SqStack *&S,ElemType e)
{
    if(S->top==MaxSize-1) return false;
    S->top++;
    S->data[S->top]=e;
    return true;
}

bool Pop(SqStack *&S,ElemType &e)
{
    if(S->top==-1) return false;
    e=S->data[S->top];
    S->top--;
    return true;
}

bool GetTop(SqStack *S,ElemType &e)
{
    if(S->top==-1) return false;
    e=S->data[S->top];
    return true;
}

typedef double ElemType1;
typedef struct 
{
    ElemType1 data[MaxSize];   
    int top;   //栈顶元素在data数组中的下标
}SqStack1;

void InitStack1(SqStack1 *&S)
{
    S=(SqStack1*)malloc(sizeof(SqStack1));
    S->top=-1;
}

void DestroyStack1(SqStack1 *&S)
{
    free(S);
}

bool StackEmpty1(SqStack1 *S)
{
    return(S->top==-1);
}

bool Push1(SqStack1 *&S,ElemType1 e)
{
    if(S->top==MaxSize-1) return false;
    S->top++;
    S->data[S->top]=e;
    return true;
}

bool Pop1(SqStack1 *&S,ElemType1 &e)
{
    if(S->top==-1) return false;
    e=S->data[S->top];
    S->top--;
    return true;
}

bool GetTop1(SqStack1 *S,ElemType1 &e)
{
    if(S->top==-1) return false;
    e=S->data[S->top];
    return true;
}