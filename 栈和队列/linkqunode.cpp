#include <stdio.h>
#include <stdlib.h>

// 链队列的节点结构
typedef int ElemType;  // 假设元素类型为int，可根据需要修改

typedef struct qNode {
    ElemType data;
    struct qNode *next;
} DataNode;

// 链队列结构
typedef struct {
    DataNode *front;  // 队头指针
    DataNode *rear;   // 队尾指针
} LinkQueue;

// 1. 初始化队列
void InitQueue(LinkQueue *&Q) {
    Q=(LinkQueue*)malloc(sizeof(LinkQueue));
    Q->front=Q->rear=NULL;
}

// 2. 销毁队列
void DestroyQueue(LinkQueue *&Q) {
    DataNode *pre=Q->front,*p;
    if(pre!=NULL)
    {
        p=pre->next;
        while (p!=NULL)
        {
            free(pre);
            pre=p;
            p=p->next;
        }
    }
    free(pre);
}

// 3. 判断队列是否为空
int QueueEmpty(LinkQueue *Q) {
    return Q->rear== NULL;
}

// 4. 进队操作
void enQueue(LinkQueue *&Q, ElemType e) {
    DataNode *p = (DataNode*)malloc(sizeof(DataNode));
    p->data = e;
    p->next = NULL;
    if (Q->rear==NULL)
    {
        Q->front=Q->rear=p;
    }
    else
    {
        Q->rear->next = p;
        Q->rear = p;
    }
}

// 5. 出队操作
bool deQueue(LinkQueue *&Q, ElemType &e) {
    if (Q->rear == NULL) return false;
    DataNode *t=Q->front;
    if(Q->front==Q->rear)
    {
        Q->front=Q->rear=NULL;
    }
    else
    {
        Q->front=Q->front->next;
    }
    e = t->data;
    free(t);
    return true;
}

