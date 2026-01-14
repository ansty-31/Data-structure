#include <stdio.h>

int climbingSteps(int nsteps)
{
    if(nsteps==1)
    {
        return 1;
    }
    else if(nsteps==2)
    {
        return 2;
    }
    else
    {
        return climbingSteps(nsteps-1)+climbingSteps(nsteps-2);
    }
}

int main()
{
    int nsteps=5;
    printf("%d",climbingSteps(nsteps));
}