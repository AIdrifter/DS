#include<stdlib.h>
#include<string.h>
#include"stack.h"
struct stack_t{
	char * array;
	size_t cap, tSize, size;
};

typedef struct stack_t stack;

struct stack_t * stackAlloc()
{
	return malloc(sizeof(stack));
}

int stackInit(struct stack_t* pThis, size_t tSize, size_t cap)
{
	pThis->cap=cap;
	pThis->tSize=tSize;
	pThis->size=0;
	pThis->array=(char*)malloc(tSize*cap);
	return (pThis->array!=NULL)?__DS__STACK__NORMAL__:__DS__STACK__OUT_OF_MEM__;
}

int stackPush(struct stack_t* pThis, const void * pObj)
{
	if(pThis->size==pThis->cap)
		return __DS__STACK__FULL__;
	memcpy(pThis->array+pThis->size*pThis->tSize, pObj, pThis->tSize);
	pThis->size++;
	return __DS__STACK__NORMAL__;
}

int stackPop(struct stack_t *pThis, void *pRet)
{
	if(!pThis->size)
		return __DS__STACK__EMPTY__;
	pThis->size--;
	memcpy(pRet, pThis->array+pThis->size*pThis->tSize, pThis->tSize);
	return __DS__STACK__NORMAL__;
}

int stackEmpty(struct stack_t *pThis)
{
	return !pThis->size;
}

int stackTop(struct stack_t *pThis, void *pRet)
{
	if(!pThis->size)
		return __DS__STACK__EMPTY__;
	memcpy(pRet, pThis->array+(pThis->size-1)*pThis->tSize, pThis->tSize);
	return __DS__STACK__NORMAL__;
}

size_t stackCap(struct stack_t *pThis)
{
	return pThis->cap;
}

size_t stackSize(struct stack_t *pThis)
{
	return pThis->size;
}

size_t stackTypeSize(struct stack_t *pThis)
{
	return pThis->tSize;
}

int stackFree(struct stack_t* pThis)
{
	if(pThis->array)
		free(pThis->array);
	free(pThis);
	return __DS__STACK__NORMAL__;
}
