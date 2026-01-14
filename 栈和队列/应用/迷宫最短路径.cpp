#include "StType -- maze.cpp"

int mg[6][6] = {
    {1,1,1,1,1,1},
    {1,0,0,0,1,1},
    {1,0,1,0,0,1},
    {1,0,0,0,1,1},
    {1,1,0,0,0,1},
    {1,1,1,1,1,1}
    };

bool mgpath(int xi, int yi, int xe, int ye)
{
    Box e;
    int i, j ,di, i1,j1,k,count=0,minlength=MaxSize;
    bool find;
    StType *st,*minst;
    InitStack(st);
    InitStack(minst);
    e.i=xi;e.j=yi;e.di=-1;
    Push(st,e);
    mg[xi][yi]=-1;
    while (!StackEmpty(st))
    {
        GetTop(st,e);
        i=e.i;j=e.j;di=e.di;
        if(i==xe&&j==ye)
        {
            count++;
            int length = st->top + 1;
            if (length < minlength)
            {
                minlength = length;
                DestroyStack(minst);
                StType *minst;
                InitStack(minst);
                for (k = 0; k <= st->top; k++) 
                {
                    Push(minst, st->data[k]);
                } 
            }
            printf("第%d条迷宫路径:\n",count);
           for (k = 0; k <= st->top; k++) {
                printf("\t(%d,%d)", st->data[k].i, st->data[k].j);
                if ((k + 1) % 5 == 0) printf("\n");
            }
            printf("\n");
            Pop(st,e);
            mg[e.i][e.j]=0;
            continue;
        }
        find = false;
        while(di<4&&!find)
        {
            di++;
            switch (di)
            {
                case 0:i1=i-1;j1=j; break;
                case 1:i1=i;j1=j+1; break;
                case 2:i1=i+1;j1=j; break;
                case 3:i1=i;j1=j-1; break;
            }
            if(mg[i1][j1]==0) find=true; 
        }
        if(find)
        {
            st->data[st->top].di=di; 
            e.i=i1;e.j=j1;e.di=-1;
            Push(st,e);
            mg[i1][j1]=-1;   
        }
        else
        {

            Pop(st,e);
            mg[e.i][e.j]=0;  
        }
    }
    printf("最短路径长为%d\n",minlength);
    printf("最短路径为\n");
    for (k = 0; k <= minst->top; k++) {
            printf("\t(%d,%d)", minst->data[k].i, minst->data[k].j);
            if ((k + 1) % 5 == 0) printf("\n");
        }
    printf("\n");
    DestroyStack(st);
    DestroyStack(minst);
    return count>0;
}

int main()
{
    if(!mgpath(1,1,4,4))
    {
        printf("该迷宫问题没有解!");
    }
    return 0;
}
