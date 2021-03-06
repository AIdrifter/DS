#include "pq_b.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int doubleGT(const void *a, const void *b);

/* Hash Map spec */
#define __DS__HM__NORMAL__        0x00000000
#define __DS__HM__OUT_OF_MEM__    0x00000001
#define __DS__HM__KEY_EXIST__     0x00000002
#define __DS__HM__KEY_NOT_EXIST__ 0x00000004
struct hm_t;

struct hm_t *hmAlloc();
int hmInit(struct hm_t *pThis, size_t keySize, size_t valSize);
int hmFree(struct hm_t *pThis);

int hmSize(struct hm_t *pThis);
int hmInsert(struct hm_t *pThis, void *pKey, void *pVal);
int hmDelete(struct hm_t *pThis, void *pKey);
int hmGet(struct hm_t *pThis, void *pKey, void *pRetVal);
int hmSet(struct hm_t *pThis, void *pKey, void *pNewVal);
int hmKeyExist(struct hm_t *pThis, void *pKey);
/* Hash Map spec end */
void hmDebug(struct hm_t*);

inline char* getAddr(void *array, int i, size_t tSize){
	return array+i*tSize;
}
inline void getItem(void *array, int i, void* pRet, size_t tSize){
	memcpy(pRet, array+i*tSize, tSize);
}
inline void putItem(void *array, int i, const void* pRet, size_t tSize){
	memcpy(array+i*tSize, pRet, tSize);
}

/* Very Slow Priority Queue implementation */
struct pq_t{
    void *keyArray;
    void *objArray;
    size_t keySize, objSize, size, cap;
    struct hm_t *pObjToIndex;
    int (*cmp)(const void*, const void*);
    int dynamic;
};

/*
void pqDebug(struct pq_t* pThis){
    printf("size/cap: %zu/%zu\nkey,obj size: %zu, %zu\n", pThis->size, pThis->cap, pThis->keySize, pThis->objSize);
    size_t i;
    printf("keyArray, objArray: %x, %x\n", pThis->keyArray, pThis->objArray);
    printf("key:");
    for(i=0; i<pThis->size; i++){
        printData(__DS__DOUBLE__, pThis->keyArray + i*pThis->keySize);
        printf("%c", (i!=(pThis->size-1))?' ':'\n');
    }
    printf("obj:");
    for(i=0; i<pThis->size; i++){
        printData(__DS__SHORT__, pThis->objArray + i*pThis->objSize);
        printf("%c", (i!=(pThis->size-1))?' ':'\n');
    }
    printf("pObjToIndex:\n");
    hmDebug(pThis->pObjToIndex);
}
*/

struct pq_t *pqAlloc(){
    return malloc(sizeof(struct pq_t));
}

int pqInit(struct pq_t *pThis, size_t keySize, size_t objSize, size_t cap, int (*cmp)(const void*, const void*)){
    if(cap != 0){
        pThis->dynamic = 0;
        pThis->keySize = keySize;
        pThis->objSize = objSize;
        pThis->size = 0;
        pThis->cap = cap;
        pThis->keyArray = malloc(cap * keySize);
        pThis->objArray = malloc(cap * objSize);
        pThis->pObjToIndex = hmAlloc();
        pThis->cmp = cmp;
        hmInit(pThis->pObjToIndex, objSize, sizeof(size_t));
        if(pThis->keyArray == NULL || pThis->objArray == NULL || pThis->pObjToIndex == NULL)
            return __DS__PQ__OUT_OF_MEM__;
    }
    return __DS__PQ__NORMAL__;
}

int pqFree(struct pq_t *pThis){
    if(pThis->pObjToIndex != NULL)
        hmFree(pThis->pObjToIndex);
    if(pThis->keyArray != NULL)
        free(pThis->keyArray);
    if(pThis->objArray != NULL)
        free(pThis->objArray);
    free(pThis);
}

size_t pqCap(struct pq_t *pThis){
    return pThis->cap;
}
size_t pqSize(struct pq_t *pThis){
    return pThis->size;
}
size_t pqKeySize(struct pq_t *pThis){
    return pThis->keySize;
}
size_t pqObjSize(struct pq_t *pThis){
    return pThis->objSize;
}
int pqEmpty(struct pq_t *pThis){
    return pThis->size == 0;
}

int pqInsert(struct pq_t *pThis, void *pKey, void *pObj){
    if(pThis->size == pThis->cap)
        return __DS__PQ__FULL__;
    if(hmKeyExist(pThis->pObjToIndex, pObj))
        return __DS__PQ__OBJ_EXIST__;

    putItem(pThis->keyArray, pThis->size, pKey, pThis->keySize);
    putItem(pThis->objArray, pThis->size, pObj, pThis->objSize);
    hmInsert(pThis->pObjToIndex, pObj, &(pThis->size));
    pThis->size++;
    return __DS__PQ__NORMAL__;
}
int pqExtractMax(struct pq_t *pThis, void *pRetKey, void *pRetObj){
    if(pThis->size == 0)
        return __DS__PQ__EMPTY__;
    void *max = pThis->keyArray, *iter;
    size_t max_i = 0, i;
    for(i=1; i<pThis->size; i++){
        /* find max */
        iter = getAddr(pThis->keyArray, i, pThis->keySize);
        if((*(pThis->cmp))(max, iter) < 0){
            max = iter;
            max_i = i;
        }
    }
    getItem(pThis->keyArray, max_i, pRetKey, pThis->keySize);
    getItem(pThis->objArray, max_i, pRetObj, pThis->objSize);

    for(i=max_i; i<pThis->size-1; i++){
        void *iter1 = getAddr(pThis->keyArray, i, pThis->keySize);
        void *iter2 = getAddr(pThis->keyArray, i+1, pThis->keySize);
        memcpy(iter1, iter2, pThis->keySize);
        iter1 = getAddr(pThis->objArray, i, pThis->objSize);
        iter2 = getAddr(pThis->objArray, i+1, pThis->objSize);
        memcpy(iter1, iter2, pThis->objSize);
        hmSet(pThis->pObjToIndex, iter1, &i);
    }
    hmDelete(pThis->pObjToIndex, pRetObj);
    pThis->size--;
    return __DS__PQ__NORMAL__;
}

int pqMax(struct pq_t *pThis, void *pRetKey, void *pRetObj){
    if(pThis->size == 0)
        return __DS__PQ__EMPTY__;
    void *max = pThis->keyArray, *iter;
    size_t max_i = 0, i;
    for(i=1; i<pThis->size; i++){
        /* find max */
        iter = getAddr(pThis->keyArray, i, pThis->keySize);
        if((*(pThis->cmp))(max, iter) < 0){
            max = iter;
            max_i = i;
        }
    }
    getItem(pThis->keyArray, max_i, pRetKey, pThis->keySize);
    getItem(pThis->objArray, max_i, pRetObj, pThis->objSize);

    return __DS__PQ__NORMAL__;
}

/* bonus2 */
int pqExtractMin(struct pq_t *pThis, void *pRetKey, void *pRetObj){
    if(pThis->size == 0)
        return __DS__PQ__EMPTY__;
    void *min = pThis->keyArray, *iter;
    size_t min_i = 0, i;
    for(i=1; i<pThis->size; i++){
        /* find min */
        iter = getAddr(pThis->keyArray, i, pThis->keySize);
        if((*(pThis->cmp))(min, iter) > 0){
            min = iter;
            min_i = i;
        }
    }
    getItem(pThis->keyArray, min_i, pRetKey, pThis->keySize);
    getItem(pThis->objArray, min_i, pRetObj, pThis->objSize);

    for(i=min_i; i<pThis->size-1; i++){
        void *iter1 = getAddr(pThis->keyArray, i, pThis->keySize);
        void *iter2 = getAddr(pThis->keyArray, i+1, pThis->keySize);
        memcpy(iter1, iter2, pThis->keySize);
        iter1 = getAddr(pThis->objArray, i, pThis->objSize);
        iter2 = getAddr(pThis->objArray, i+1, pThis->objSize);
        memcpy(iter1, iter2, pThis->objSize);
        hmSet(pThis->pObjToIndex, iter1, &i);
    }
    hmDelete(pThis->pObjToIndex, pRetObj);
    pThis->size--;
    return __DS__PQ__NORMAL__;
}
int pqMin(struct pq_t *pThis, void *pRetKey, void *pRetObj){
    if(pThis->size == 0)
        return __DS__PQ__EMPTY__;
    void *min = pThis->keyArray, *iter;
    size_t min_i = 0, i;
    for(i=1; i<pThis->size; i++){
        /* find min */
        iter = getAddr(pThis->keyArray, i, pThis->keySize);
        if((*(pThis->cmp))(min, iter) > 0){
            min = iter;
            min_i = i;
        }
    }
    getItem(pThis->keyArray, min_i, pRetKey, pThis->keySize);
    getItem(pThis->objArray, min_i, pRetObj, pThis->objSize);

    return __DS__PQ__NORMAL__;
}

/* bonus3 */
int pqGetKey(struct pq_t *pThis, void *pObj, void *pRetKey){
    size_t index;
    if(hmGet(pThis->pObjToIndex, pObj, &index) == __DS__HM__KEY_NOT_EXIST__ )
        return __DS__PQ__OBJ_NOT_EXIST__;
    getItem(pThis->keyArray, index, pRetKey, pThis->keySize);
    return __DS__PQ__NORMAL__;
}

int pqChangeKey(struct pq_t *pThis, void *pObj, void *pNewKey){
    size_t index;
    if(hmGet(pThis->pObjToIndex, pObj, &index) == __DS__HM__KEY_NOT_EXIST__)
        return __DS__PQ__OBJ_NOT_EXIST__;
    putItem(pThis->keyArray, index, pNewKey, pThis->keySize);
    return __DS__PQ__NORMAL__;
}

/* Very Slow Hash Map Implementation */
#define MIN_HASH_CAP 8
struct hm_t{
    void *keyArray;
    void *valArray;
    size_t size, cap, keySize, valSize;
};

struct hm_t *hmAlloc(){
    return malloc(sizeof(struct hm_t));
}

/*
void hmDebug(struct hm_t* pThis){
    printf("size/cap: %zu/%zu\nkey,val size: %zu, %zu\n", pThis->size, pThis->cap, pThis->keySize, pThis->keySize);
    size_t i;
    printf("key:");
    for(i=0; i<pThis->size; i++){
        printData(__DS__SHORT__, pThis->keyArray + i*pThis->keySize);
        printf("%c", (i!=(pThis->size-1))?' ':'\n');
    }
    printf("val:");
    for(i=0; i<pThis->size; i++){
        printData(__DS__SHORT__, pThis->valArray + i*pThis->valSize);
        printf("%c", (i!=(pThis->size-1))?' ':'\n');
    }
}
*/

int hmInit(struct hm_t *pThis, size_t keySize, size_t valSize){
    pThis->size = 0;
    pThis->cap = MIN_HASH_CAP;
    pThis->keySize = keySize;
    pThis->valSize = valSize;

    pThis->keyArray = malloc(pThis->keySize*pThis->cap);
    if(pThis->keyArray == NULL)
        return __DS__HM__OUT_OF_MEM__;
    pThis->valArray = malloc(pThis->valSize*pThis->cap);
    if(pThis->valArray == NULL){
        free(pThis->keyArray);
        return __DS__HM__OUT_OF_MEM__;
    }
}
int hmFree(struct hm_t *pThis){
    if(pThis->keyArray)
        free(pThis->keyArray);
    if(pThis->valArray)
        free(pThis->valArray);
    free(pThis);
}

int hmExpand(struct hm_t *pThis){
    if(pThis->size == pThis->cap){
        pThis->cap = 2*pThis->cap;

        pThis->keyArray = realloc(pThis->keyArray, pThis->keySize*pThis->cap);
        if(pThis->keyArray == NULL)
            return __DS__HM__OUT_OF_MEM__;
        pThis->valArray = realloc(pThis->valArray, pThis->valSize*pThis->cap);
        if(pThis->valArray == NULL){
            free(pThis->keyArray);
            return __DS__HM__OUT_OF_MEM__;
        }
    }
    return __DS__HM__NORMAL__;
}
int hmShrink(struct hm_t *pThis){
    if(pThis->size*4 <= pThis->cap && pThis->size > MIN_HASH_CAP){
        pThis->cap = pThis->cap/2;

        pThis->keyArray = realloc(pThis->keyArray, pThis->keySize*pThis->cap);
        if(pThis->keyArray == NULL)
            return __DS__HM__OUT_OF_MEM__;
        pThis->valArray = realloc(pThis->valArray, pThis->valSize*pThis->cap);
        if(pThis->valArray == NULL){
            free(pThis->keyArray);
            return __DS__HM__OUT_OF_MEM__;
        }
    }
    return __DS__HM__NORMAL__;
}
int hmSize(struct hm_t *pThis){
    return pThis->size;
}
int hmInsert(struct hm_t *pThis, void *pKey, void *pVal){
    if(hmKeyExist(pThis, pKey))
        return __DS__HM__KEY_EXIST__;
    if(pThis->size == pThis->cap)
        if(hmExpand(pThis) == __DS__HM__OUT_OF_MEM__ )
            return __DS__HM__OUT_OF_MEM__;
    memcpy(pThis->keyArray + pThis->size*pThis->keySize, pKey, pThis->keySize);
    memcpy(pThis->valArray + pThis->size*pThis->valSize, pVal, pThis->valSize);
    pThis->size++;
    return __DS__HM__NORMAL__;
}
int hmFindKey(struct hm_t *pThis, void *pKey){
    int i;
    for(i=0; i<pThis->size; i++){
        void *iter = pThis->keyArray + i*pThis->keySize;
        if(memcmp(iter, pKey, pThis->keySize) == 0)
            break;
    }
    return i;
}
int hmDelete(struct hm_t *pThis, void *pKey){
    int i = hmFindKey(pThis, pKey);
    if(i == pThis->size)
        return __DS__HM__KEY_NOT_EXIST__;
    if(i != pThis->size-1){
        void *leftEnd = pThis->keyArray + i*pThis->keySize;
        void *rightStart = pThis->keyArray + (i+1)*pThis->keySize;
        size_t rightSize = pThis->keySize*(pThis->size-(i+1));
        memmove(leftEnd, rightStart, rightSize);

        leftEnd = pThis->valArray + i*pThis->valSize;
        rightStart = pThis->valArray + (i+1)*pThis->valSize;
        rightSize = pThis->valSize*(pThis->size-(i+1));
        memmove(leftEnd, rightStart, rightSize);
    }
    pThis->size--;
    if(pThis->size*4 <= pThis->cap && pThis->size > MIN_HASH_CAP)
        if(hmShrink(pThis) == __DS__HM__OUT_OF_MEM__ )
            return __DS__HM__OUT_OF_MEM__;

    return __DS__HM__NORMAL__;
    
}
int hmGet(struct hm_t *pThis, void *pKey, void *pRetVal){
    int i = hmFindKey(pThis, pKey);
    if(i == pThis->size)
        return __DS__HM__KEY_NOT_EXIST__;
    memcpy(pRetVal, pThis->valArray + i*pThis->valSize, pThis->valSize);
    return __DS__HM__NORMAL__;
}
int hmSet(struct hm_t *pThis, void *pKey, void *pNewVal){
    int i = hmFindKey(pThis, pKey);
    if(i == pThis->size)
        return __DS__HM__KEY_NOT_EXIST__;
    memcpy(pThis->valArray + i*pThis->valSize, pNewVal, pThis->valSize);
    return __DS__HM__NORMAL__;
}
int hmKeyExist(struct hm_t *pThis, void *pKey){
    int i = hmFindKey(pThis, pKey);
    if(i == pThis->size)
        return 0;
    return 1;
}
/* Hash Map Implementation End */
