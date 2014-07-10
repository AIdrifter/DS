#include <stdlib.h>
#ifndef __ds__rmq__header__
#define __ds__rmq__header__

#define __DS__RMQ__NORMAL__       0x00000000
#define __DS__RMQ__FULL__         0x00000001
#define __DS__RMQ__EMPTY__        0x00000002
#define __DS__RMQ__OUT_OF_MEM__   0x00000004
#define __DS__RMQ__OUT_OF_SIZE__  0x00000008
#define __DS__RMQ__OUT_OF_CAP__   0x00000010
#define __DS__RMQ__OUT_OF_ORDER__ 0x00000020

/* rmq: DS support 1D range maximum query (p.s. rmqRangeMax) */
struct rmq_t;

struct rmq_t *rmqAlloc();
/* Allocate memory for rmq. Return NULL if not enough memory */

int rmqInit(struct rmq_t *pThis, size_t tSize, size_t cap, int (*gt)(const void *, const void *), void *pNegInf);
/* Initialize pThis: set the size per object as tSize
 * and the capacity as cap.
 * the comparsion function as gt
 * the negative infinity of object (negInf <= everything of the object) as *pNegInf
 * After the initialization, there's nothing. So size is 0.
 * Return 0 for normal execution.
 * Bonus: Using dynamic capacity when cap=0.
 * Hint: You can initial elements with negative infinity.
 */

int rmqFree(struct rmq_t *pThis);
/* Release the memory.
 * Deep release: You should release the memory allocated by any operation.
 * Return 0 for normal execution.
 */

/* Property Access */

size_t rmqCap(struct rmq_t *pThis);
/* return current capacity */

size_t rmqSize(struct rmq_t *pThis);
/* return number of elements in the container */

size_t rmqTypeSize(struct rmq_t *pThis);
/* return the size of object in the container */

int rmqEmpty(struct rmq_t *pThis);
/* return zero if container isn't empty */

/* Element access */

int rmqGet(struct rmq_t *pThis, size_t index, void *pRet);
/* Get the value of container[index]
 * Write the result to *pRet.
 * Return 0 for normal execution.
 * Return __DS__RMQ__OUT_OF_SIZE__ if index >= size or index < 0.
 */

/* Modifier */

int rmqPushBack(struct rmq_t *pThis, const void *pObj);
/* push the object into the back of container.
 * Return __DS__RMQ__FULL__, if there's no space for the object.
 * Note: Dynamic version should return __DS__RMQ__OUT_OF_MEM__ in such condition.
 * Increment size and return 0 for normal execution.
 */

int rmqPopBack(struct rmq_t *pThis, void *pRet);
/* pop the object from the back of container.
 * Write the result to *pRet.
 * Return __DS__RMQ__EMPTY__, if there's nothing to be popped.
 * Decrement size and return 0 for normal execution.
 */

int rmqSetCap(struct rmq_t *pThis, size_t newCap);
/* Change the capacity of container from oldCap to newCap.
 * For elements beyond newCap, drop them and reduce size to newCap, return __DS__RMQ__OUT_OF_CAP__ .
 * If the system couldn't offer enough memory for resizing, return __DS__RMQ__OUT_OF_MEM__ .
 * Otherwise, return 0 for normal execution.
 */

int rmqSet(struct rmq_t *pThis, size_t index, const void *pObj);
/* Set one element in container by the object *pObj.
 * Return 0 for normal execution.
 * Return __DS__RMQ__OUT_OF_SIZE__ if index >= size or < 0.
 * Performance requirement: O(logn)-time per operation.
 */

/* Operations */

int rmqRangeMax(struct rmq_t *pThis, size_t start, size_t end, void *pRet);
/* Get the Maximum value for elements in container where index >= start && index <= end.
 * Write the result to *pRet.
 * Note: the first element has index 0.
 * Return 0 for normal execution.
 * Return __DS__RMQ__OUT_OF_SIZE__  if end >= capacity or start < 0.
 * Return __DS__RMQ__OUT_OF_ORDER__ if start > end.
 * Performance requirement: O(logn)-time per operation.
 */

#endif
