#include <stdio.h>
#include <malloc.h>

//采用邻接表存储
typedef struct ANode
{
    int adjvex;
    struct ANode *nextarc;
    int weight;
}ArcNode;  //边节点类型
typedef struct 	  
{
   InfoType info;        //顶点信息
   int count;           //增加存放顶点入度
   ArcNode *firstarc;   //指向第一条边
} VNode;
typedef struct 
{
    VNode adjlist[MAXV];  //邻接表数组
    int n, e;
}AdjGraph;

void TopSort(AdjGraph *G)		//拓扑排序算法
{
   int St[MAXV],top=-1;		//栈St的指针为top
   for (int i=0;i<G->n;i++)	//入度置初值0
      G->adjlist[i].count=0;
   for (int i=0;i<G->n;i++) //求所有顶点的入度
   {	
      for (ArcNode *p = G->adjlist[i].firstarc; p; p=p->nextarc)
        G->adjlist[p->adjvex].count++;
   }
   for (i=0;i<G->n;i++)		//将入度为0的顶点进栈
     if (G->adjlist[i].count==0)
       St[++top]=i;
   while (top>-1) {			//栈不空循环
      int i = St[top--];		//出栈一个顶点i
      printf("%d ", i);		//输出该顶点
	//for遍历i的所有出邻接点
      for (ArcNode * p=G->adjlist[i].firstarc; p; p=p->nextarc) {	   //将顶点i的出边邻接点的入度减1
         int j=p->adjvex;
	  G->adjlist[j].count--;
	  if (G->adjlist[j].count==0)	//将入度为0的邻接点进栈
           St[++top]=j;
      }
   }
}


