#include "graph.h"

int dist(AajGraph* G, int start, int end)
{
    ArcNode* p;
    int w, i,distance=0;
    QUEUE qu[MAXV];
    int front = -1, rear = -1;
    int visited[MAXV]={0};
    for (i = 0; i < G->n; i++) visited[i] = 0;  //初始化访问标志数组
    rear++;
    qu[rear].data = start;
    qu[rear].parent = -1;
    visited[start] = 1;
    int find=0;
    while (front != rear)
    {
        front++;
        w = qu[front].data;
        if (w == end)
        {
            i=front;
            while (qu[i].parent != -1)
            {
                distance++;
                i--;
            }
            if(distance!=0) distance--;
            find=1;
        }
        p = G->adjlist[w].firstarc;
        while (p != NULL)
        {
            if (!visited[p->adjvex])
            {
                visited[p->adjvex] = 1;
                rear++;
                qu[rear].data = p->adjvex;
                qu[rear].parent = w;
            }
            p = p->nextarc;
        }
    }
    if(find==1)
        return distance;
    else
        return -1;
}

