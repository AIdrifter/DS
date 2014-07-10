#include<stdlib.h>
#include<string.h>
#include"heap.h"
struct heap_t{
	char *a; /* array */
	size_t cap, tSize, size;
	int (*gt)(const void *, const void *);
};

typedef struct heap_t heap;
typedef int (*cmp)(const void*,const void*);

heap *heapAlloc(void)
{
	return (heap *)malloc(sizeof(heap));
}

inline char* getAddr(heap *pThis, int i)
{
	return pThis->a+i*pThis->tSize;
}

inline void getItem(heap *pThis, int i, void* pRet)
{
	memcpy(pRet, pThis->a+i*pThis->tSize, pThis->tSize);
}

inline void putItem(heap *pThis, int i, const void* pItem)
{
	memcpy(pThis->a+i*pThis->tSize, pItem, pThis->tSize);
}

int heapInit(heap *pThis, size_t tSize, size_t cap, cmp gt)
{
	pThis->a=(char*)malloc(tSize*cap);
	pThis->cap=cap;
	pThis->tSize=tSize;
	pThis->size=0;
	pThis->gt=gt;
	if(pThis->a==NULL)return __DS__HEAP__OUT_OF_MEM__;
	return __DS__HEAP__NORMAL__;
}

int heapPush(heap *pThis, const void *pObj)
{
	if(pThis->size==pThis->cap)
		return __DS__HEAP__FULL__;
	putItem(pThis,pThis->size,pObj);
	pThis->size++;
	return __DS__HEAP__NORMAL__;
}

int heapPop(heap *pThis, void *pRet)
{
	void *max;
	char *iter;
	if(pThis->size==0)return __DS__HEAP__EMPTY__;
	max=pThis->a;
	for(iter=getAddr(pThis,1); iter<getAddr(pThis,pThis->size); iter+=pThis->tSize)
		if(pThis->gt(iter,max)>0)max=iter;
	memcpy(pRet, max, pThis->tSize);
	pThis->size--;
	for(iter=(char*)max; iter<getAddr(pThis,pThis->size); iter+=pThis->tSize)
		memcpy(iter, iter+pThis->tSize, pThis->tSize);
	return __DS__HEAP__NORMAL__;
}

int heapEmpty(heap *pThis)
{
	return !(pThis->size);
}

int heapTop(heap *pThis, void *pRet)
{
	void *max;
	char *iter;
	if(pThis->size==0)return __DS__HEAP__EMPTY__;
	max=pThis->a;
	for(iter=getAddr(pThis,1); iter<getAddr(pThis,pThis->size); iter+=pThis->tSize)
		if(pThis->gt(iter,max)>0)max=iter;
	memcpy(pRet, max, pThis->tSize);
	return __DS__HEAP__NORMAL__;
}

size_t heapCap(heap *pThis)
{
	return pThis->cap;
}

size_t heapSize(heap *pThis)
{
	return pThis->size;
}


size_t heapTypeSize(heap *pThis)
{
	return pThis->tSize;
}

int heapFree(heap *pThis)
{
	if(pThis->a)
		free(pThis->a);
	free(pThis);
	return __DS__HEAP__NORMAL__;
}
