#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <malloc.h>

#define MAXV 100  //图的最大顶点数
#define INF 65535  //表示无穷大
#define InfoType char  //顶点其他信息类型

typedef struct {
    int data; //顶点编号
    int parent; //父节点编号
}QUEUE;  //队列结点类型

typedef struct 
{
    int no;  //顶点编号
    InfoType info;   //顶点其他信息
} VertexType;  //顶点类型

typedef struct 
{
    int edges[MAXV][MAXV];  //邻接矩阵
    VertexType vexs[MAXV];  //顶点数组
    int n, e;  //图的当前顶点数和边数
} MatGraph;  //图的邻接矩阵类型

typedef struct ANode {
    int adjvex;  //该边的邻接点编号
    struct ANode* nextarc;  //指向下一条边的指针
    int weight;  //边的权值
} ArcNode;    //边结点的类型

typedef struct VNode {
    InfoType info;  //顶点的其他信息
    ArcNode* firstarc;  //指向第一个边结点
} VNode;    //头结点的类型

typedef struct {
    VNode adjlist[MAXV];  //邻接表
    int n, e;  //图的当前顶点数和边数
} AajGraph;    //图的邻接表类型

// 邻接表创建与显示
void CreateAdj(AajGraph* &G, int A[MAXV][MAXV], int n, int e);
void DispAdj(AajGraph* G);
void DestroyAdj(AajGraph* &G);

// 深度优先遍历
void DFS(AajGraph* G, int v);
void DFSTraverse(AajGraph* G);

// 广度优先遍历
void BFS(AajGraph* G, int v);
void BFSTraverse(AajGraph* G);

// Dijkstra算法求最短路径(邻接矩阵类型)
void DijkstraM(MatGraph* G, int v0);
void DispathM(MatGraph* G, int dist[], int path[], int S[], int v0); 
// Dijkstra算法求最短路径(邻接表类型)
void DijkstraA(AajGraph* G, int v0);
void DispathA(AajGraph* G, int dist[], int path[], int S[], int v0);

// 计算两点间最短路径长度
int dist(AajGraph* G, int start, int end);

#endif 