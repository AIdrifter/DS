#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"stack.h"
#include"utility.h"

typedef struct stack_t stack;

int main()
{
	stack *p=NULL;
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
			puts("The stack needs to be initialized.");
			printf("Init step 1. d for double, others for short: ");
			scanf("%s",cmd);
			type=(cmd[0]=='d')?__DS__DOUBLE__:__DS__SHORT__;
			printf("Init step 2. Capacity: ");
			scanf("%zu",&cap);
			p=stackAlloc();
			ret=stackInit(p,cmd[0]=='d'?sizeof(double):sizeof(short),cap);
			if(ret)
			{
				puts("Not enough memory.");
				stackFree(p);
				p=NULL;
			}
			else
				puts("Initialization done.");
		}
		else
		{
			printf("size/capacity: %zu/%zu\n", stackSize(p), stackCap(p));
			tSize=stackTypeSize(p);
			puts("Valid operations: 1)push 2)pop 3)top 4)empty 5)free 6)quit");
			for(choice=0;choice<=0||choice>6;sscanf(cmd,"%d",&choice))
				scanf("%s",cmd);
			if(choice==1)
			{
				printf("Input a %s value:",tSize==sizeof(double)?"double":"short");
				getData(type,data);
				ret=stackPush(p,data);
				if(ret)puts("The stack is full!");
			}
			else if(choice==2)
			{
				ret=stackPop(p,data);
				if(!ret)
				{
					printf("The result is ");
					printData(type,data);
					puts(".");
				}
				else
					puts("The stack is empty!");
			}
			else if(choice==3)
			{
				ret=stackTop(p,data);
				if(!ret)
				{
					printf("The result is ");
					printData(type,data);
					puts(".");
				}
				else
					puts("The stack is empty!");
			}
			else if(choice==4)
			{
				if(stackEmpty(p))puts("The stack is empty.");
				else puts("The stack is not empty.");
			}
			else if(choice==5)
			{
				stackFree(p);
				p=NULL;
			}
			else
				break;
		}
	}
	return 0;
}
