#include "graph.h"

// Dijkstra(邻接矩阵类型)
void DijkstraM(MatGraph G, int v0) {
    int dist[MAXV];  //存储源点到各顶点的最短路径长度
    int path[MAXV];  //存储源点到各顶点的 最短路径上的前驱顶点
    int S[MAXV];     //标记顶点是否已加入最短路径集合
    int i, j, k, min;
    ArcNode* p;

    // 初始化 dist{}、path{}、S{}
    for (i=0; i < G.n; i++) 
    {
        dist[i] = G.edges[v0][i];
        if (G.edges[v0][i] < INF && i != v0) {
            path[i] = v0;
        } else {
            path[i] = -1; // -1表示没有前驱顶点
        }
        S[i] = 0; // 初始时所有顶点都未加入集合S
    }

    S[v0] = 1;path[v0]=0; // 源点加入集合S
    for (i = 1; i < G.n; i++)  //循环直到算有顶点的最短路径都求出
    {
        min = INF;
        // 找到不在S中且dist最小的顶点k
        for (j = 0; j < G.n; j++) {
            if (!S[j] && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }

        S[k] = 1; // 将顶点k加入集合S

        // 更新dist和path数组
        for (j = 0; j < G->n; j++) {
            if (!S[j] && G->edges[k][j] < INF) {
                if (dist[k] + G->edges[k][j] < dist[j]) {
                    dist[j] = dist[k] + G->edges[k][j];
                    path[j] = k;
                }
            }
        }
        printf("\nVertex %d added to S:", k);
        for (int m = 0; m < G->n; m++) {  //显示当前dist数组
            if (dist[m] == INF)
                printf(" INF");
            else
                printf(" %d", dist[m]);
        }
    }
    DispathM(G,dist,path,S,v0);  //显示最短路径结果(最短路径上的都是最短)
}

void DispathM(MatGraph G, int dist[], int path[], int S[], int v0) {
    int i, j;
    printf("Shortest paths from vertex %d:\n", v0);
    for (i = 0; i < G.n; i++) {
        if (i != v0) {
            if (dist[i] == INF) {
                printf("No path to vertex %d\n", i);
            } else {
                printf("To vertex %d: distance = %d, path = ", i, dist[i]);
                // 输出路径
                j = i;
                int stack[MAXV], top = -1;
                while (j != v0) {  //回溯路径(先找到的后输出,用栈)
                    stack[++top] = j;
                    j = path[j];
                }
                printf("%d", v0);
                while (top != -1) {  //输出路径
                    printf(" -> %d", stack[top--]);
                }
                printf("\n");
            }
        }
    }
}

//Dijkstra(邻接表类型)
void DijkstraA(AajGraph *G, int v0) {
    int dist[MAXV];  //存储源点到各顶点的最短路径长度
    int path[MAXV];  //存储源点到各顶点的最短路径上的前驱顶点
    int S[MAXV];     //标记顶点是否已加入最短路径集合
    int i, j, k, min;
    ArcNode* p;
    // 初始化
    for (i=0; i < G->n; i++) {
        dist[i] = INF;
        path[i] = -1; // -1表示没有前驱顶点
        S[i] = 0; // 初始时所有顶点都未加入集合S
    }
    dist[v0] = 0;
    S[v0] = 1;path[v0]=0; // 源点加入集合S
    for (i = 1; i < G->n; i++) {
        min = INF;
        // 找到不在S中且dist最小的顶点k
        for (j = 0; j < G->n; j++) {
            if (!S[j] && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }

        S[k] = 1; // 将顶点k加入集合S

        // 更新dist和path数组
        p = G->adjlist[k].firstarc;
        while (p != NULL) {
            j = p->adjvex;
            if (!S[j]) {
                if (dist[k] + p->weight < dist[j]) {
                    dist[j] = dist[k] + p->weight;
                    path[j] = k;
                }
            
            }
            p = p->nextarc;
        }
        printf("\nVertex %d added to S:", k);
        for (int m = 0; m < G->n; m++) {  //显示当前dist数组
            if (dist[m] == INF)
                printf(" INF");
            else
                printf(" %d", dist[m]);
        }
    }
    DispathA(G,dist,path,S,v0);  //显示最短路径结果
}

void DispathA(AajGraph* G, int dist[], int path[], int S[], int v0) {
    int i, j;
    printf("Shortest paths from vertex %d:\n", v0);
    for (i = 0; i < G->n; i++) {
        if (i != v0) {
            if (dist[i] == INF) {
                printf("No path to vertex %d\n", i);
            } else {
                printf("To vertex %d: distance = %d, path = ", i, dist[i]);
                // 输出路径
                j = i;
                int stack[MAXV], top = -1;
                while (j != v0) {  //回溯路径
                    stack[++top] = j;
                    j = path[j];
                }
                printf("%d", v0);
                while (top != -1) {  //输出路径
                    printf(" -> %d", stack[top--]);
                }
                printf("\n");
            }
        }
    }
}