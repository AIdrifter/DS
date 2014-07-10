#include <string.h>
#include "rmq.h"

/* rmq: DS support 1D range maximum query (p.s. rmqRangeMax) */
struct rmq_t {
    void* array;
    size_t cap, size, tSize;
    int (*gt)(const void*, const void*);
    void* pNegInf;
    int dynamic;
};

typedef struct rmq_t rmq;


struct rmq_t *rmqAlloc(){
    return malloc(sizeof(rmq));
}
/* Allocate memory for rmq. Return NULL if not enough memory */

int rmqInit(struct rmq_t *pThis, size_t tSize, size_t cap, int (*gt)(const void *, const void *), void *pNegInf){
    if(cap != 0){
        pThis->cap = cap;
        pThis->tSize = tSize;
        pThis->array = malloc(cap*tSize);
        if(!pThis->array){ return __DS__RMQ__OUT_OF_MEM__; }
        pThis->size = 0;
        pThis->gt = gt;
        pThis->pNegInf = malloc(tSize); // pNegInf;
        if(!pThis->pNegInf){ free(pThis->array); return __DS__RMQ__OUT_OF_MEM__; }
        memcpy(pThis->pNegInf, pNegInf, tSize);
        pThis->dynamic = 0;
        int i;
        for(i=0; i<cap; i++)
            memcpy(pThis->array + i*tSize, pThis->pNegInf, tSize);

        return __DS__RMQ__NORMAL__;
    }
}
/* Initialize pThis: set the size per object as tSize
 * and the capacity as cap.
 * the comparsion function as gt
 * the negative infinity of object (negInf <= everything of the object) as *pNegInf
 * After the initialization, there's nothing. So size is 0.
 * Return 0 for normal execution.
 * Bonus: Using dynamic capacity when cap=0.
 * Hint: You can initial elements with negative infinity.
 */

int rmqFree(struct rmq_t *pThis){
    if(!pThis->array)
        free(pThis->array);
    if(!pThis->pNegInf)
        free(pThis->pNegInf);
    free(pThis);
    return __DS__RMQ__NORMAL__;
}
/* Release the memory.
 * Deep release: You should release the memory allocated by any operation.
 * Return 0 for normal execution.
 */

/* Property Access */

size_t rmqCap(struct rmq_t *pThis){
    return pThis->cap;
}

size_t rmqSize(struct rmq_t *pThis){
    return pThis->size;
}

size_t rmqTypeSize(struct rmq_t *pThis){
    return pThis->tSize;
}

int rmqEmpty(struct rmq_t *pThis){
    return (pThis->size) == 0;
}

/* Element access */

int rmqGet(struct rmq_t *pThis, size_t index, void *pRet){
    if(index >= pThis->size)
        return __DS__RMQ__OUT_OF_SIZE__;
    memcpy(pRet, pThis->array + index*pThis->tSize, pThis->tSize);
    return __DS__RMQ__NORMAL__;
}
/* Get the value of container[index]
 * Write the result to *pRet.
 * Return 0 for normal execution.
 * Return __DS__RMQ__OUT_OF_SIZE__ if index >= size or index < 0.
 */

/* Modifier */

int rmqPushBack(struct rmq_t *pThis, const void *pObj){
	if(!pThis->dynamic){
	    if(pThis->size == pThis->cap)
	        return __DS__RMQ__FULL__;
        memcpy(pThis->array + pThis->size*pThis->tSize, pObj, pThis->tSize);
        pThis->size++;
        return __DS__RMQ__NORMAL__;
    }
}
/* push the object into the back of container.
 * Return __DS__RMQ__FULL__, if there's no space for the object.
 * Note: Dynamic version should return __DS__RMQ__OUT_OF_MEM__ in such condition.
 * Increment size and return 0 for normal execution.
 */

int rmqPopBack(struct rmq_t *pThis, void *pRet){
    if(pThis->size == 0)
        return __DS__RMQ__EMPTY__;
    if(!pThis->dynamic){
        memcpy(pRet, pThis->array + (pThis->size-1)*(pThis->tSize), pThis->tSize);
        memcpy(pThis->array + (pThis->size-1)*(pThis->tSize), pThis->pNegInf, pThis->tSize);
        pThis->size--;
        return __DS__RMQ__NORMAL__;
    }
}
/* pop the object from the back of container.
 * Write the result to *pRet.
 * Return __DS__RMQ__EMPTY__, if there's nothing to be popped.
 * Decrement size and return 0 for normal execution.
 */

int rmqSetCap(struct rmq_t *pThis, size_t newCap){
    void *newarray = malloc(newCap*pThis->tSize);
    if(newarray == NULL) { return __DS__RMQ__OUT_OF_MEM__; }
    int copyCap = pThis->cap, i;
    if(copyCap > newCap)
        copyCap = newCap;
    for(i=0; i<copyCap; i++)
        memcpy(newarray + i*pThis->tSize, pThis->array + i*pThis->tSize, pThis->tSize);
    for(; i<newCap; i++)
        memcpy(newarray + i*pThis->tSize, pThis->pNegInf, pThis->tSize);

    free(pThis->array);
    pThis->array = newarray;
    pThis->cap = newCap;
    if(newCap < pThis->size)
        pThis->size = newCap;
    return __DS__RMQ__NORMAL__;
}
/* Change the capacity of container from oldCap to newCap.
 * For elements beyond newCap, drop them and reduce size to newCap, return __DS__RMQ__OUT_OF_CAP__ .
 * If the system couldn't offer enough memory for resizing, return __DS__RMQ__OUT_OF_MEM__ .
 * Otherwise, return 0 for normal execution.
 */

int rmqSet(struct rmq_t *pThis, size_t index, const void *pObj){
    if(index >= pThis->size)
        return __DS__RMQ__OUT_OF_SIZE__;
	memcpy(pThis->array + index*pThis->tSize, pObj, pThis->tSize);
	return __DS__RMQ__NORMAL__;
}
/* Set one element in container by the object *pObj.
 * Return 0 for normal execution.
 * Return __DS__RMQ__OUT_OF_SIZE__ if index >= size or < 0.
 * Performance requirement: O(logn)-time per operation.
 */

/* Operations */

int rmqRangeMax(struct rmq_t *pThis, size_t start, size_t end, void *pRet){
    if(end >= pThis->size)
        return __DS__RMQ__OUT_OF_SIZE__;
    if(start > end)
        return __DS__RMQ__OUT_OF_ORDER__;
    int i;
    memcpy(pRet, pThis->pNegInf, pThis->tSize);
    for(i=start; i<=end; i++){
        if(pThis->gt(pThis->array + i*pThis->tSize, pRet) > 0)
            memcpy(pRet, pThis->array + i*pThis->tSize, pThis->tSize);
    }
    return __DS__RMQ__NORMAL__;
}
/* Get the Maximum value for elements in container where index >= start && index <= end.
 * Write the result to *pRet.
 * Return 0 for normal execution.
 * Return __DS__RMQ__OUT_OF_SIZE__  if end >= capacity or start < 0.
 * Return __DS__RMQ__OUT_OF_ORDER__ if start > end.
 * Performance requirement: O(logn)-time per operation.
 */
