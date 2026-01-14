#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <stdio.h>

double taile(int n)
{
    double sum = 2.0;
    long long int t=1;
    for(int i=2;i<=n;i++)
    {
        t=t*i;
        sum += 1/(double)t;
    }
    return sum;
}

int main()
{
    double e=0.0;
    e=taile(18);
    printf("e=%.50f",e);
    return 0;
}
