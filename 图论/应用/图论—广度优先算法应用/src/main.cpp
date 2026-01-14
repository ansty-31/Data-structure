#include "graph.h"

int main()
{
    int n, e, k;
    int results[20]; 
    printf("Enter number of animals and pairs:\n");
    scanf("%d %d\n", &n, &e);
    int A[MAXV][MAXV]={0};
    for (int m=0; m<e; m++)
    {
        int i, j;
        scanf("%d %d\n", &i, &j);
        A[i][j]=1;
        A[j][i]=1;
    }
    AajGraph* G;
    CreateAdj(G, A, n, e);
    scanf("%d", &k);
    for (int i = 0; i < k; i++) 
    {
        int a, b;
        scanf("%d %d", &a, &b);
        
        int distance = dist(G, a, b);
        if (distance == -1) results[i] = -1;
        else results[i] = distance;
    }
    printf("Results:\n");
    for (int i = 0; i < k; i++) 
    {
        printf("%d\n", results[i]);
    }
    DestroyAdj(G);
    return 0;
}