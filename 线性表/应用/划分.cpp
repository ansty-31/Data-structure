#include "..\sqlist.cpp"

void fun(SqList *& L)
{
	int i=0, j=L->length-1, pivot=L->data[0];
	while(i<j)
	{
		while(j>i&&L->data[j]>0)
		{
			j--;
		}
		L->data[i]=L->data[j];
		while(i<j&&L->data[i]<=0)
		{
			i++;
		}
		L->data[j]=L->data[i];
	}
	L->data[i]=pivot;
}


