#include "graph.h"

void CreateAdj(AajGraph* &G,int A[MAXV][MAXV], int n, int e) {
     G = (AajGraph*)malloc(sizeof(AajGraph));
    int i, j;ArcNode* p;
    for (i = 0; i < n; i++) {
        //对于结点自身信息处理：G->adjlist[i].info = 'A' + i; //假设顶点信息为字符'A'+i
        G->adjlist[i].firstarc = NULL;  //初始化边表为空
    }
    for (i=0;i<n;i++) {   //逐行扫描邻接矩阵
        for (j=0;j<n;j++) {
            if (A[i][j] != 0 && A[i][j] != INF) { //存在边
                p = (ArcNode*)malloc(sizeof(ArcNode));  
                p->adjvex = j;  
                p->weight = A[i][j];
                p->nextarc = G->adjlist[i].firstarc; //将新边插入表头
                G->adjlist[i].firstarc = p;
            }
        }
    }
    G->n = n;
    G->e = e;
}

void DispAdj(AajGraph* G) {  //显示邻接表
    int i; ArcNode* p;
    for (i = 0; i < G->n; i++) {
        printf("Vertex %d:", i);
        p = G->adjlist[i].firstarc;
        while (p != NULL) {
            printf(" -> (to: %d, weight: %d)", p->adjvex, p->weight);
            p = p->nextarc;
        }
        printf("\n");
    }
}

void DestroyAdj(AajGraph* &G) {  //销毁邻接表
    int i; ArcNode* pre, * p;
    for (i = 0; i < G->n; i++) {
        pre = G->adjlist[i].firstarc;
        if(pre != NULL) {
            p = pre->nextarc;
            while (p != NULL) {
                free(pre);
                pre = p;
                p = p->nextarc;
            }
            free(pre);
        }
    }
    free(G);
}

int visited[MAXV];  //创立访问标志数组

void DFS(AajGraph* G, int v) {  //深度优先遍历(连通图)
    ArcNode* p;
    for (int i = 0; i < G->n; i++) visited[i] = 0;  //初始化访问标志数组
    visited[v] = 1;
    printf("Visited vertex %d\n", v);
    p = G->adjlist[v].firstarc;
    while (p != NULL) {
        if (!visited[p->adjvex]) {
            DFS(G, p->adjvex);
        }
        p = p->nextarc;
    }
}

void DFSTraverse(AajGraph* G) {  //深度优先遍历(非连通图)
    int v;
    for (int i = 0; i < G->n; i++) visited[i] = 0;  //初始化访问标志数组
    for (v = 0; v < G->n; v++) {
        if (!visited[v]) {
            DFS(G, v);
        }
    }
}

void BFS(AajGraph* G, int v) {  //广度优先遍历(连通图)
    int queue[MAXV], front = 0, rear = 0;  //环形队列
    ArcNode* p;
    for (int i = 0; i < G->n; i++) visited[i] = 0;  //初始化访问标志数组
    visited[v] = 1;
    printf("Visited vertex %d\n", v);
    queue[rear++] = v;  //入队
    while (front != rear) {
        v = queue[front++];  //出队
        p = G->adjlist[v].firstarc;
        while (p != NULL) {
            if (!visited[p->adjvex]) {
                visited[p->adjvex] = 1;
                printf("Visited vertex %d\n", p->adjvex);
                queue[rear++] = p->adjvex;  //入队
            }
            p = p->nextarc;
        }
    }
}

void BFSTraverse(AajGraph* G) {  //广度优先遍历(非连通图)
    int v;
    for (int i = 0; i < G->n; i++) visited[i] = 0;  //初始化访问标志数组
    for (v = 0; v < G->n; v++) {
        if (!visited[v]) {
            BFS(G, v);
        }
    }
}