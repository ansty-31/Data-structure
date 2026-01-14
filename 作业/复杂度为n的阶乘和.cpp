#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <stdio.h> 

int factSum( int n) 
{
	int sum = 0,t=1;
	for(int i=1;i<=n;i++)
	{
		sum=sum+t;
		t=t*(i+1);		 
	}
	return sum;
}

int main() {
      int m = factSum( 2 );
      printf( "%d\n", m );
	  return 0;
}
