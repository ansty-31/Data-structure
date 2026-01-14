#include "..\sqlist.cpp"

void fun(SqList *& L, ElemType x, ElemType y)
{
	int k = 0;
	for(int i = 0;i<L->length;i++)
	{
		if(L->data[i]<x||L->data[i]>y)
		{
			L->data[k]=L->data[i];
			k++;
		}
	}
	L->length=k;	
} 
// 该函数的功能是删除顺序表L中所有值在x和y之间（包括x和y）的元素
