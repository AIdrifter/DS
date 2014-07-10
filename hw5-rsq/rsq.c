#include <string.h>
#include "rsq.h"

/* rsq: DS support 1D range sum query (p.s. rsqRangeSum) */
struct rsq_t {
    void* array;
    size_t cap, size, tSize;
    void (*sum)(const void *a, const void *b, void *pRet);
    void (*negate)(const void *pObj, void *pRet);
    void* pZero;
    int dynamic;
};

typedef struct rsq_t rsq;

struct rsq_t *rsqAlloc(){
    return malloc(sizeof(rsq));
}

int rsqInit(struct rsq_t *pThis, size_t tSize, size_t cap, void (*sum)(const void *, const void *, void *), void (*neg)(const void *, void *), void *pZero){
    if(cap != 0){
        pThis->cap = cap;
        pThis->tSize = tSize;
        pThis->array = malloc(cap*tSize);
        if(!pThis->array){ return __DS__RSQ__OUT_OF_MEM__; }
        pThis->size = 0;
        pThis->sum = sum;
        pThis->negate = neg;
        pThis->pZero= malloc(tSize); 
        if(!pThis->pZero){ free(pThis->array); return __DS__RSQ__OUT_OF_MEM__; }
        memcpy(pThis->pZero, pZero, tSize);
        pThis->dynamic = 0;
        int i;
        for(i=0; i<cap; i++)
            memcpy(pThis->array + i*tSize, pThis->pZero, tSize);

        return __DS__RSQ__NORMAL__;
    }
}
/* Initialize pThis: set the size per object as tSize
 * and the capacity as cap.
 * the additive operation as sum.
 * the negate function as neg.
 * the additive identity(zero constant) of object as *pZero.
 * Return 0 for normal execution.
 * Bonus: Using dynamic capacity when cap=0.
 * Bonus2: Implement without negate function.
 * Hint: You can initial elements with additive identity.
 */

int rsqFree(struct rsq_t *pThis){
    if(!pThis->array)
        free(pThis->array);
    if(!pThis->pZero)
        free(pThis->pZero);
    free(pThis);
    return __DS__RSQ__NORMAL__;
}
/* Release the memory.
 * Deep release: You should release the memory allocated by any operation.
 * Return 0 for normal execution.
 */

/* Property Access */

size_t rsqCap(struct rsq_t *pThis){
    return pThis->cap;
}

size_t rsqSize(struct rsq_t *pThis){
    return pThis->size;
}

size_t rsqTypeSize(struct rsq_t *pThis){
    return pThis->tSize;
}

int rsqEmpty(struct rsq_t *pThis){
    return (pThis->size) == 0;
}

/* Element access */

int rsqGet(struct rsq_t *pThis, size_t index, void *pRet){
    if(index >= pThis->size)
        return __DS__RSQ__OUT_OF_SIZE__;
    memcpy(pRet, pThis->array + index*pThis->tSize, pThis->tSize);
    return __DS__RSQ__NORMAL__;
}
/* Get the value of container[index]
 * Write the result to *pRet.
 * Return 0 for normal execution.
 * Return __DS__RSQ__OUT_OF_SIZE__ if index >= size.
 */

/* Modifier */

int rsqPushBack(struct rsq_t *pThis, const void *pObj){
	if(!pThis->dynamic){
	    if(pThis->size == pThis->cap)
	        return __DS__RSQ__FULL__;
        memcpy(pThis->array + pThis->size*pThis->tSize, pObj, pThis->tSize);
        pThis->size++;
        return __DS__RSQ__NORMAL__;
    }
}
/* push the object into the back of container.
 * Return __DS__RSQ__FULL__, if there's no space for the object.
 * Note: Dynamic version should return __DS__RSQ__OUT_OF_MEM__ in such condition.
 * Increment size and return 0 for normal execution.
 */

int rsqPopBack(struct rsq_t *pThis, void *pRet){
    if(pThis->size == 0)
        return __DS__RSQ__EMPTY__;
    if(!pThis->dynamic){
        memcpy(pRet, pThis->array + (pThis->size-1)*(pThis->tSize), pThis->tSize);
        memcpy(pThis->array + (pThis->size-1)*(pThis->tSize), pThis->pZero, pThis->tSize);
        pThis->size--;
        return __DS__RSQ__NORMAL__;
    }
}
/* pop the object from the back of container.
 * Write the result to *pRet.
 * Return __DS__RSQ__EMPTY__, if there's nothing to be popped.
 * Decrement size and return 0 for normal execution.
 */

int rsqSetCap(struct rsq_t *pThis, size_t newCap){
    void *newarray = malloc(newCap*pThis->tSize);
    if(newarray == NULL) { return __DS__RSQ__OUT_OF_MEM__; }
    int copyCap = pThis->cap, i;
    if(copyCap > newCap)
        copyCap = newCap;
    for(i=0; i<copyCap; i++)
        memcpy(newarray + i*pThis->tSize, pThis->array + i*pThis->tSize, pThis->tSize);
    for(; i<newCap; i++)
        memcpy(newarray + i*pThis->tSize, pThis->pZero, pThis->tSize);

    free(pThis->array);
    pThis->array = newarray;
    pThis->cap = newCap;
    if(pThis->size > newCap)
        pThis->size = newCap;
    return __DS__RSQ__NORMAL__;
}
/* Change the capacity of container from oldCap to newCap.
 * For elements beyond newCap, drop them and reduce size to newCap, return __DS__RSQ__OUT_OF_CAP__ .
 * If the system couldn't offer enough memory for resizing, return __DS__RSQ__OUT_OF_MEM__ .
 * Otherwise, return 0 for normal execution.
 */

int rsqSet(struct rsq_t *pThis, size_t index, const void *pObj){
    if(index >= pThis->size)
        return __DS__RSQ__OUT_OF_SIZE__;
	memcpy(pThis->array + index*pThis->tSize, pObj, pThis->tSize);
	return __DS__RSQ__NORMAL__;
}
/* Set one element in container by the object *pObj.
 * Return 0 for normal execution.
 * Return __DS__RSQ__OUT_OF_SIZE__ if index >= size or < 0.
 * Performance requirement: O(logn)-time per operation.
 */

/* Operations */

int rsqRangeSum(struct rsq_t *pThis, size_t start, size_t end, void *pRet){
    if(end >= pThis->size)
        return __DS__RSQ__OUT_OF_SIZE__;
    if(start > end)
        return __DS__RSQ__OUT_OF_ORDER__;
    int i;
    memcpy(pRet, pThis->pZero, pThis->tSize);
    for(i=start; i<=end; i++){
        void *temp = malloc(pThis->tSize);
        pThis->sum(pThis->array + i*pThis->tSize, pRet, temp);
        memcpy(pRet, temp, pThis->tSize);
        free(temp);
    }
    return __DS__RSQ__NORMAL__;
}
/* Get the Sum for elements in container where index >= start && index <= end.
 * Write the result to *pRet.
 * Return 0 for normal execution.
 * Return __DS__RSQ__OUT_OF_SIZE__  if end >= size.
 * Return __DS__RSQ__OUT_OF_ORDER__ if start > end.
 */
