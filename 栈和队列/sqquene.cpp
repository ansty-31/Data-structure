#include <stdio.h>
#include <malloc.h>

typedef int ElemType;

#define MaxSize 50

typedef struct 
{
    ElemType data[MaxSize];
    int front, rear; //队头和队尾指针
}SqQueue;

//顺序队列(保留队外数据，适合广度遍历)
void InitQueue(SqQueue *&q)
{
    q=(SqQueue *)malloc(sizeof(SqQueue));
    q->front = q->rear = -1;
}

void DestroyQueue(SqQueue *&q)
{
    free(q);
}

int QueueEmpty(SqQueue *q)
{
    return (q->front==q->rear);
}

bool enQueue(SqQueue *&q, ElemType e)
{
    if(q->rear==MaxSize-1)
    {
        return false;
    }
    q->rear++;
    q->data[q->rear]=e;
    return true;
}

bool deQueue(SqQueue *&q, ElemType &e)
{
    if(q->front==q->rear) 
    {
        return ture;
    }
    q->front++;
    e=q->data[q->front];
    return true;
}

//环形顺序队列（防止假溢出）
void init_queue(SqQueue *&q)
{
    q=(SqQueue *)malloc(sizeof(SqQueue));
    q->front=q->rear=0;
}

void destory_queue(SqQueue *&q)
{
    free(q);
}

bool queue_empty(SqQueue *q)
{
    return(q->front==q->rear);
}

bool en_queue(SqQueue *&q, ElemType e)
{
    if((q->rear+1)%MaxSize==q->front)
    {
        return false;
    }
    q->rear=(q->rear+1)%MaxSize;
    q->data[q->rear]=e;
    return true;
}

bool de_queue(SqQueue *&q, ElemType e)
{
    if(q->front==q->rear)
    {
        return true;
    }
    q->front=(q->front+1)%MaxSize;
    q->data[q->front]=e;
    return true;
}