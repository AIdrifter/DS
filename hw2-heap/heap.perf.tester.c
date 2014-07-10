#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"heap.h"

typedef struct heap_t heap;

int gt(const void *a, const void *b)
{
	int da=*(int*)a;
	int db=*(int*)b;
	if(da==db)return 0;
	return (da>db)?1:-1;
}

int main()
{
	int i,n,x;
	heap *p=NULL;
	p=heapAlloc();
	scanf("%d",&n);
	heapInit(p,sizeof(int),n+1,gt);
	for(i=0;i<n/2;i++)
	{
		x=i+n/2;
		heapPush(p,&x);
	}
	for(i=0;i<n/2;i++)
		heapPush(p,&i);
	while(!heapEmpty(p))
	{
		heapPop(p,&x);
		printf("%d%c",x,heapEmpty(p)?'\n':' ');
	}
	return 0;
}
