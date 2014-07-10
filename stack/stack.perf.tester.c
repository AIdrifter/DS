#include<stdio.h>
#include"stack.h"

typedef struct stack_t stack;
typedef struct{
	int depth,symbol;
}config;

int main()
{
	stack *ptr;
	config c;
	int i, errCode,n;
	int array[15];
	int usedPos[16]={0};
	scanf("%d",&n);
	ptr = stackAlloc();
	stackInit(ptr, sizeof(config), 15);
	c.depth=0;
	c.symbol=0;
	stackPush(ptr,&c);
	do{
		config data, newData;
		stackPop(ptr,&data);
		if(data.depth==n)
		{
			for(i=0;i<n;i++)printf("%d%c",array[i],(i<n-1)?' ':'\n');
		}
		else
		{
			usedPos[data.symbol]=0;
			for(data.symbol++; data.symbol <= n && usedPos[data.symbol]>0; data.symbol++);
			if(data.symbol<=n)
			{
				array[data.depth]=data.symbol;
				usedPos[data.symbol]++;
				newData.depth=data.depth+1;
				newData.symbol=0;
				stackPush(ptr,&data);
				stackPush(ptr,&newData);	
			}
		}
	}while(!stackEmpty(ptr));
	return 0;
}
