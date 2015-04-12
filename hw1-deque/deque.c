#include<stdlib.h>
#include<string.h>
#include"deque.h"
//  replace pThis -> p
typedef struct deque_t queue;

int dequeTracerse(struct deque_t *p,void *obj ,size_t i){
    if(i<=p->rear){
        memcpy(obj,p->array+p->tSize*i,p->tSize);
        return 0;
    }
    else
        return -1;
}

struct deque_t *dequeAlloc(){
    return malloc(sizeof(queue));
}

int dequeInit(struct deque_t *p, size_t tSize, size_t cap){
    p->cap=cap;
    p->tSize=tSize;// double ??
    // p->array=(char*)malloc(tSize*cap);
    p->array=(char*)calloc(cap,tSize);
    // give '\0'
    //memset(p, '\0',tSize*cap);
    p->rear=0;
    return (p->array!=NULL)?__DS__DEQUE__NORMAL__:__DS__DEQUE__OUT_OF_MEM__;
}

int dequeFree(struct deque_t *p){
    if(p!=NULL){
        if(p->array!=NULL){
            free(p->array);
        }
        free(p);
    }
	return __DS__DEQUE__NORMAL__;
}

// shift all element
int dequePushFront(struct deque_t *p, const void *pObj){
    if(p->rear==p->cap)
        return __DS__DEQUE__FULL__;

    // shift array
    memcpy(p->array + p->tSize, p->array , p->tSize*p->rear );

    // push
    memcpy(p->array, pObj , p->tSize );
    p->rear++;
    return __DS__DEQUE__NORMAL__;
}

// FIFO(normal queue , first in first out)
int dequePushBack(struct deque_t *p, const void *pObj){
    if(p->rear==p->cap)
        return __DS__DEQUE__FULL__;

    memcpy(p->array + p->rear*p->tSize, pObj, p->tSize );
    p->rear++;
    return __DS__DEQUE__NORMAL__;
}

int dequePopFront(struct deque_t *p, void *pRet){
    if(p->rear==0)
        return __DS__DEQUE__EMPTY__;

    memcpy(pRet, p->array, p->tSize);
    memcpy(p->array, p->array + p->tSize , p->tSize*(p->rear-1) );
    p->rear--;
    return __DS__DEQUE__NORMAL__;
}

int dequePopBack(struct deque_t *p, void *pRet){
    if(p->rear==0)
        return __DS__DEQUE__EMPTY__;
    memcpy(pRet, p->array + p->tSize*(p->rear-1), p->tSize);
    p->rear--;
    return __DS__DEQUE__NORMAL__;
}

int dequeEmpty(struct deque_t *p){
    return  !p->rear;
}

int dequeFront(struct deque_t *p, void *pRet){
    if(p->rear==0)
        return __DS__DEQUE__EMPTY__;

    memcpy(pRet, p->array, p->tSize);
    return __DS__DEQUE__NORMAL__;
}

int dequeBack(struct deque_t *p, void *pRet){
    if(p->rear==0)
        return __DS__DEQUE__EMPTY__;
    memcpy(pRet, p->array + p->tSize*(p->rear-1), p->tSize);
    return __DS__DEQUE__NORMAL__;
}

size_t dequeCap(struct deque_t *p){
	return p->cap;
}

size_t dequeSize(struct deque_t *p){
	return p->rear;
}

size_t dequeTypeSize(struct deque_t *p){
	return p->tSize;
}
