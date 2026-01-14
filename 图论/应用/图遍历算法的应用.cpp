#include "..\graph.cpp"

//深度优先算法：所有结果
void FindAllPath(AdjGraph *G, int u, int v, int path[],int d)
{
    //这里d初值为-1
    int w,i;ArcNode *p;
    d++;path[d]=u;
    visited[u]=1;
    if(u==v&&d>=0)  //由于每一轮的path都属于那一轮特有，所有在这里设置d==l的话，可以实现只输出长度为l的简单路径
    {
        for(i=0;i<=d;i++)
        {
            printf("%2d",path[i]);
        }
        printf("\n");
    }
    //深度遍历算法
    p=G->adjlist[v].firstarc;
    while (p!=NULL)
    {
        w=p->adjvex;
        if(visited[w]==0) FindAllPath(G,w,v,path,d); //每次调用的都是上一轮的path，回溯的时候保证还是原来的path
        p=p->nextarc;
    }
    //回溯
    visited[u]=0;  //调用的时候，回溯的是那一轮的u，也就是w
}

/*广度优先算法：最短路径(为了能回溯输出，采样非环形队列)，参考translat.cpp中的dist
 核心：类似树一样，要记得前一个位置parent（初值为-1），利于输出的时候while到，遍历和BFS没区别*/

 //距离v最远的点——广度优先算法
 int Maxdist(AdjGraph *G, int v)
{
    int w,i;ArcNode *p;
    SqQueue *qu;
    init_queue(qu);
    for(i=0;i<G->n;i++) visited[i]=0;
    visited[v]=1;
    enQueue(qu,v);
    while (!queue_empty(qu))  //由于是环形队列，空的时候说明遍历完了
    {
        de_queue(qu,w);  //出队，取出数据
        p=G->adjlist[w].firstarc;
        while(p!=NULL)
        {
            if(visited[p->adjvex]==0)
            {
                visited[p->adjvex]=1;
                en_queue(qu,p->adjvex);
            }
            p=p->nextarc;
        }
    }
    return w;
}

//图遍历法求解迷宫问题：FindAllPath与dist改
/*教材上写的是构建迷宫对应的邻接表
typedef struct MNode
{
    int i,j;
    struct MNode *nextmrc;
}MrcNode;   //迷宫的边结点类型
typedef struct Znode
{
    MrcNode *firstmrc;   
}ZNode;      //迷宫的头结点类型
typedef struct 
{
    ZNode adjlist[MAXV+2][MAXV+2];
}MazeGraph;*/
int mvisited[MAXV+2][MAXV+2]={0};

//但算法没变，不过是编号从一维变成二维，所以只需要用一维代替二维（函数映射），或者根据迷宫邻居数为4，直接写
void mazeDFS(int maze[][], int x, int y, int endx, int endy, int pathx[],int pathy[], int d)
{
    if(x<1||x>MAXV||y<1||y>MAXV||maze[x][y]==1||mvisited[x][y]==1) return;
    d++; //d初值也是-1
    pathx[d]=x;
    pathy[d]=y;
    mvisited[x][y]=1;
    if(x==endx&&y==endy)
    {
        for(int i=0;i<=d;i++)
        {
            printf("(%d,%d)",pathx[d],pathy[d]);
        }
        printf("\n");
    }
    mazeDFS(maze,x+1,y,endx,endy,pathx,pathy,d);
    mazeDFS(maze,x,y-1,endx,endy,pathx,pathy,d);
    mazeDFS(maze,x-1,y,endx,endy,pathx,pathy,d);
    mazeDFS(maze,x,y+1,endx,endy,pathx,pathy,d);
    mvisited[x][y]=0;
}





