#include <stdio.h>
#include <malloc.h>
#include "D:\C&C++\栈和队列\sqquene.cpp"

//邻接矩阵存储
#define MAXV 50
#define INF 32767
typedef struct 
{
    int no;  
    InfoType info;
}VertexType;  //顶点类型
typedef struct 
{
    int edges[MAXV][MAXV];  //邻接矩阵数组
    int n,e;  //顶点数和边数
    VertexType vex[MAXV];  //存放顶点信息
}MatGraph;  //完整的邻接矩阵定义

//邻接表存储
typedef struct ANode
{
    int adjvex;
    struct ANode *nextarc;
    int weight;
}ArcNode;  //边节点类型
typedef struct Vnode
{
    InfoType info;
    ArcNode *firstarc;
}VNode;   //头节点类型
typedef struct 
{
    VNode adjlist[MAXV];  //邻接表数组
    int n, e;
}AdjGraph;

//邻接矩阵->邻接表
void MatToList(MatGraph g, AdjGraph *G)
{
    int i, j;
    ArcNode *p;
    G=(AdjGraph*)malloc(sizeof(AdjGraph));
    for(i=0;i<g.n;i++)
    {
        G->adjlist[i].firstarc=NULL;
    }
    for(i=0;i<g.n;i++)
    {
        for(j=g.n-1;j>=0;j--)
        {
            if(g.edges[i][j]!=0&&g.edges[i][j]!=INF)
            {
                p=(ArcNode*)malloc(sizeof(ArcNode));
                p->adjvex=j;
                p->weight=g.edges[i][j];
                p->nextarc=G->adjlist[i].firstarc;
                G->adjlist[i].firstarc=p;
            }
        }
    }
    G->n=g.n;G->e=g.e;
}
//邻接表->邻接矩阵
void ListToMat(AdjGraph *G, MatGraph &g)
{
    int i;
    ArcNode *p;
    for(i=0;i<G->n;i++)
    {
        p=G->adjlist[i].firstarc;
        while(p!=NULL)
        {
            g.edges[i][p->adjvex]=p->weight;
            p=p->nextarc;
        }
    }
    g.e=G->e;g.n=G->n;
}


//图的基本运算函数（以邻接表为例，因为邻接表较为常用）
void CreateAdj(AdjGraph *&G, int A[MAXV][MAXV],int n, int e)
{
    int i,j;ArcNode *p;
    G=(AdjGraph*)malloc(sizeof(AdjGraph));
    for(i=0;i<n;i++)
    {
        G->adjlist[i].firstarc=NULL;
    }  //初始化
    for(i=0;i<n;i++)
    {
        for(j=n-1;j>=0;j--)
        {
            if (A[i][j]!=0&&A[i][j]!=INF)
            {
                p=(ArcNode*)malloc(sizeof(ArcNode));
                p->adjvex=j;
                p->weight=A[i][j];
                p->nextarc=G->adjlist[i].firstarc;
                G->adjlist[i].firstarc=p; //头插法，所以从n-1开始
            }
        }
    }
    G->n=n;G->e=e;
}

void DispAdj(AdjGraph *G)
{
    int i;ArcNode *p;
    for(i=0;i<G->n;i++)
    {
        p=G->adjlist[i].firstarc;
        printf("%3d: ",i);
        while(p!=NULL)
        {
            printf("%3d[%d]->",p->adjvex,p->weight);
            p=p->nextarc;
        }
        printf("^\n");
    }
}

void DesytoryAdj(AdjGraph *&G)
{
    int i;ArcNode *p,*pre;
    for(i=0;i<G->n;i++)
    {
        pre=G->adjlist[i].firstarc;
        if(pre->nextarc!=NULL)
        {
            p=pre->nextarc;
            while(p!=NULL)
            {
                free(pre);
                pre=p;
                p=pre->nextarc;
            }
            free(pre);
        }
    }
    free(G);  //别忘了头节点数组
}

//深度优先遍历（需要全局数组——DFS要递归）
int visited[MAXV]={0};
void DFS(AdjGraph *G,int v)
{
    ArcNode *p;
    visited[v]=1;
    printf("%d",v);
    p=G->adjlist[v].firstarc;
    while(p!=NULL)
    {
        if(visited[p->adjvex]==0) DFS(G,p->adjvex);
        p=p->nextarc;
    }
}

//广度优先遍历(visited可以内置，因为没法递归,环形队列实现！毕竟只是遍历，最短路径看应用)
void BFS(AdjGraph *G,int v)
{
    int w,i;ArcNode *p;
    SqQueue *qu;
    init_queue(qu);
    for(i=0;i<G->n;i++) visited[i]=0;
    printf("%2d",v);
    visited[v]=1;
    enQueue(qu,v);
    while (!queue_empty(qu))
    {
        de_queue(qu,w);  //出队，取出数据
        p=G->adjlist[w].firstarc;
        while(p!=NULL)
        {
            if(visited[p->adjvex]==0)
            {
                printf("%d",p->adjvex);
                visited[p->adjvex]=1;
                en_queue(qu,p->adjvex);
            }
            p=p->nextarc;
        }
    }
    printf("\n");
} //类似二叉树层次遍历

//非连通图的遍历，注意visited数组一开始最好初始化置零一下
void DFS1(AdjGraph *G)
{
    int i;
    for(i=0;i<G->n;i++)
    {
        if(visited[i]==0) DFS(G,i);
    }
}
void BFS1(AdjGraph *G)
{
    int i;
    for(i=0;i<G->n;i++)
    {
        if(visited[i]==0) BFS(G,i);
    }
}

