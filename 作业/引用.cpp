#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <stdio.h>

void getmaxmin ( int A[], int n, int &max, int &min ) 
{
    max = A[0];
    for(int i=1;i<n;i++)
    {
        if(A[i]>max)
        {
            max = A[i];
        }
    }
    min = A[0];
    for(int i=1;i<n;i++)
    {
        if(A[i]<min)
        {
            min = A[i];
        }
    }
}
     

int main() {
    int a[] = { 1, 100, 12, 3123, 123111, -10, -1023, 0, 1, 12 };
    int max, min;
    getmaxmin( a, 10, max, min);
    printf("%d/%d\n", max, min);
    return 0;
}
