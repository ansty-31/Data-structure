#include "graph.cpp"

typedef struct 
{
    int u;  //边的起点
    int v;  //边的终点
    int w;
}Edge;

void Kruskal(MatGraph g)
{
    int i, j, u1, v1, sn1, sn2, k;
    int vset[MAXV];
    Edge E[MAXV];
    k=0;
    for(i=0;i<g.n;i++)
    {
        for(j=0;j<=i;j++)
        {
            if(g.edges[i][j]!=0&&g.edges[i][j]!=INF)
            {
                E[k].u=i;E[k].v=j;E[k].w=g.edges[i][j];
                k++;
            }
        }
    }
    InsertSort(E,g.e);    //直接插入排序对E数组按权值递增排序
    for(i=0;i<g.n;i++)
    {
        vest[i]=i;        //初始化辅助数组
    }
    k=1;j=0;    //k表示当前构造生成树的第几条边,初值为1；j=0表示从最小的边开始遍历
    while (k<g.n)
    {
        u1=E[j].u;v1=E[j].v;
        sn1=vest[u1];
        sn2=vset[u2];
        if(sn1!=sn2)
        {
            printf("(%d,%d):%d\n",u1,v1,E[j].w)
            k++;
            for(i=0;i<g.n;i++)
            {
                if(vest[i]==sn2) vest[i]=sn1;  //集合编号为sn2改为sn1（避免生成回路）
            }
        }
        j++;
    }
    
}
