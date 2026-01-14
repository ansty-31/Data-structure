
#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <stdio.h>


void log2n(int A[],int n)
{
    for(int i = 0;i<n;i++)
    {
        double result=log2((double)A[i]);
        printf("%f ",result);
    }
    printf("\n");
}
void sqrtn(int A[],int n)
{
    for(int i=0;i<n;i++)
    {
        double result=sqrt( (double)A[i]);
        printf("%f ",result);
    }
    printf("\n");
}
void n1(int A[],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",A[i]);
    }
    printf("\n");
}
void nlog2n(int A[],int n)
{
    for(int i=0;i<n;i++)
    {
        double result=A[i]*log2( (double)A[i]);
        printf("%f ",result);
    }
    printf("\n");
}
void n2(int A[],int n)
{
    for(int i=0;i<n;i++)
    {
        int result = A[i]*A[i];
        printf("%d ",result);
    }
    printf("\n");
}
void n3(int A[],int n)
{
    for(int i = 0;i<n;i++)
    {
        int result =A[i]*A[i]*A[i];
        printf("%d ",result);
    }
    printf("\n");
}
void exp2n(int A[],int n)
{
    for(int i = 0;i<n;i++)
    {
        int result=exp2((double)A[i]);
        printf("%d ", result);
    }
    printf("\n");
}
void nn(int A[],int n)
{
    printf("%d ",A[0]);
	long long int result=1;
    for(int i = 1;i<n;i++)
    {
        result*=A[i];
        printf("%lld ",result);
    }
    printf("\n");
}
int main()
{
    int n = 0,A[100]={0};
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        A[i]=i+1;
    } 
    log2n(A,n);
    sqrtn(A,n);
    n1(A,n);
    nlog2n(A,n);
    n2(A,n);
    n3(A,n);
    exp2n(A,n);
    nn(A,n);
    return 0;

}
