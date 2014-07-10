#include <stdlib.h>
#ifndef __ds__rsq__header__
#define __ds__rsq__header__

#define __DS__RSQ__NORMAL__       0x00000000
#define __DS__RSQ__FULL__         0x00000001
#define __DS__RSQ__EMPTY__        0x00000002
#define __DS__RSQ__OUT_OF_MEM__   0x00000004
#define __DS__RSQ__OUT_OF_SIZE__  0x00000008
#define __DS__RSQ__OUT_OF_CAP__   0x00000010
#define __DS__RSQ__OUT_OF_ORDER__ 0x00000020

/* rsq: DS support 1D range sum query (p.s. rsqRangeSum) */
struct rsq_t;

struct rsq_t *rsqAlloc();
/* Allocate memory for rsq. Return NULL if not enough memory */

int rsqInit(struct rsq_t *pThis, size_t tSize, size_t cap, void (*sum)(const void *, const void *, void *), void (*neg)(const void *, void *), void *pZero);
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

int rsqFree(struct rsq_t *pThis);
/* Release the memory.
 * Deep release: You should release the memory allocated by any operation.
 * Return 0 for normal execution.
 */

/* Property Access */

size_t rsqCap(struct rsq_t *pThis);
/* return the current capacity */

size_t rsqSize(struct rsq_t *pThis);
/* return the number of elements in the container */

size_t rsqTypeSize(struct rsq_t *pThis);
/* return the size of object in the container */

int rsqEmpty(struct rsq_t *pThis);
/* return zero if container isn't empty */

/* Element access */

int rsqGet(struct rsq_t *pThis, size_t index, void *pRet);
/* Get the value of container[index]
 * Write the result to *pRet.
 * Return 0 for normal execution.
 * Return __DS__RSQ__OUT_OF_SIZE__ if index >= size.
 */

/* Modifier */

int rsqPushBack(struct rsq_t *pThis, const void *pObj);
/* push the object into the back of container.
 * Return __DS__RSQ__FULL__, if there's no space for the object.
 * Note: Dynamic version should return __DS__RSQ__OUT_OF_MEM__ in such condition.
 * Increment size and return 0 for normal execution.
 */

int rsqPopBack(struct rsq_t *pThis, void *pRet);
/* pop the object from the back of container.
 * Write the result to *pRet.
 * Return __DS__RSQ__EMPTY__, if there's nothing to be popped.
 * Decrement size and return 0 for normal execution.
 */

int rsqSetCap(struct rsq_t *pThis, size_t newCap);
/* Change the capacity of container from oldCap to newCap.
 * For elements beyond newCap, drop them and reduce size to newCap, return __DS__RSQ__OUT_OF_CAP__ .
 * If the system couldn't offer enough memory for resizing, return __DS__RSQ__OUT_OF_MEM__ .
 * Otherwise, return 0 for normal execution.
 */

int rsqSet(struct rsq_t *pThis, size_t index, const void *pObj);
/* Set one element in container by the object *pObj.
 * Return 0 for normal execution.
 * Return __DS__RSQ__OUT_OF_SIZE__ if index >= size or < 0.
 * Performance requirement: O(logn)-time per operation.
 */

/* Operations */

int rsqRangeSum(struct rsq_t *pThis, size_t start, size_t end, void *pRet);
/* Get the Sum for elements in container where index >= start && index <= end.
 * Write the result to *pRet.
 * Note: the first element has index 0.
 * Return 0 for normal execution.
 * Return __DS__RSQ__OUT_OF_SIZE__  if end >= size.
 * Return __DS__RSQ__OUT_OF_ORDER__ if start > end.
 */

#endif
