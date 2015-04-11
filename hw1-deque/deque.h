#ifndef __ds__deque__header__
#define __ds__deque__header__

#define __DS__DEQUE__NORMAL__       0x00000000
#define __DS__DEQUE__FULL__         0x00000001
#define __DS__DEQUE__EMPTY__        0x00000002
#define __DS__DEQUE__OUT_OF_MEM__   0x00000004

struct deque_t{
	char * array;
	size_t cap, tSize;
	size_t rear;
};

struct deque_t *dequeAlloc();
/* Allocate memory for a deque. Return NULL if not enough memory */

int dequeTraverse(struct deque_t *p, void *obj ,size_t i);
/**/

int dequeInit(struct deque_t *pThis, size_t tSize, size_t cap);
/* Initialize pThis: set the size per object as tSize
 * and the capacity as cap.
 * Return 0 for normal execution.
 * Bonus: Using dynamic capacity when cap=0.
 */

int dequeFree(struct deque_t *pThis);
/* Release the memory.
 * Return 0 for normal execution.
 */

int dequePushFront(struct deque_t *pThis, const void *pObj);
/* Push the object into the front of deque.
 * Return 0 for normal execution.
 */

int dequePushBack(struct deque_t *pThis, const void *pObj);
/* Push the object into the back of deque.
 * Return 0 for normal execution.
 */

int dequePopFront(struct deque_t *pThis, void *pRet);
/* Pop the object from the front of deque.
 * Write the result to *pRet.
 * Return 0 for normal execution.
 */

int dequePopBack(struct deque_t *pThis, void *pRet);
/* Pop the object from the back of deque.
 * Write the result to *pRet.
 * Return 0 for normal execution.
 */

int dequeEmpty(struct deque_t *pThis);
/* return zero if deque isn't empty */

int dequeFront(struct deque_t *pThis, void *pRet);
/* Write the object to pRet from the front of deque.
 * Return 0 for normal execution.
 */

int dequeBack(struct deque_t *pThis, void *pRet);
/* Write the object to pRet from the back of deque.
 * Return 0 for normal execution.
 */

size_t dequeCap(struct deque_t *pThis);
/* return the actual capacity */

size_t dequeSize(struct deque_t *pThis);
/* return the size of deque */

size_t dequeTypeSize(struct deque_t *pThis);
/* return the size of object in the deque */

#endif
