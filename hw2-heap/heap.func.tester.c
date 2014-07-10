#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"heap.h"
#include"utility.h"

typedef struct heap_t heap;

int doubleGT(const void *a, const void *b)
{
	double da=*(double*)a;
	double db=*(double*)b;
	if(da==db)return 0;
	return (da>db)?1:-1;
}

int shortGT(const void *a, const void *b)
{
	short da=*(short*)a;
	short db=*(short*)b;
	if(da==db)return 0;
	return (da>db)?1:-1;
}

int main()
{
	heap *p=NULL;
	char cmd[10240];
	size_t cap, tSize;
	int ret;
	void *data;
	int choice;
	int type;
	data=malloc(sizeof(double)*10);
	for(;;)
	{
		if(p==NULL)
		{
			puts("The heap needs to be initialized.");
			printf("Init step 1. d for double, others for short: ");
			scanf("%s",cmd);
			type=(cmd[0]=='d')?__DS__DOUBLE__:__DS__SHORT__;
			printf("Init step 2. Capacity: ");
			scanf("%zu",&cap);
			p=heapAlloc();
			if(cmd[0]=='d')
				ret=heapInit(p,sizeof(double),cap,doubleGT);
			else
				ret=heapInit(p,sizeof(short),cap,shortGT);
			if(ret)
			{
				puts("Not enough memory.");
				heapFree(p);
				p=NULL;
			}
			else
				puts("Initialization done.");
		}
		else
		{
			printf("size/capacity: %zu/%zu\n", heapSize(p), heapCap(p));
			tSize=heapTypeSize(p);
			puts("Valid operations: 1)push, 2)pop, 3)top, 4)empty, 5)free, 6)quit");
			for(choice=0;choice<=0||choice>6;sscanf(cmd,"%d",&choice))
				scanf("%s",cmd);
			if(choice==1)
			{
				printf("Input a %s value: ",tSize==sizeof(double)?"double":"short");
				getData(type,data);
				ret=heapPush(p,data);
				if(ret)printf("The heap is full!\n");
			}
			else if(choice==2)
			{
				ret=heapPop(p,data);
				if(!ret)
				{
					printf("The result is ");
					printData(type,data);
					puts(".");
				}
				else
					printf("The heap is empty!\n");
			}
			else if(choice==3)
			{
				ret=heapTop(p,data);
				if(!ret)
				{
					printf("The result is ");
					printData(type,data);
					puts(".");
				}
				else
					printf("The heap is empty!\n");
			}
			else if(choice==4)
			{
				if(heapEmpty(p))printf("The heap is empty.\n");
				else puts("The heap is not empty.");
			}
			else if(choice==5)
			{
				heapFree(p);
				p=NULL;
			}
			else
				break;
		}
	}
	return 0;
}
