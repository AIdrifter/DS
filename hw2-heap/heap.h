#ifndef __ds__heap__header__
#define __ds__heap__header__

#define __DS__HEAP__NORMAL__		0x00000000
#define __DS__HEAP__FULL__			0x00000001
#define __DS__HEAP__EMPTY__		0x00000002
#define __DS__HEAP__OUT_OF_MEM__	0x00000004

struct heap_t;
/* Heaps store various but fixed-size data */
/* Support customized comparison */

struct heap_t *heapAlloc();
/* Allocate memory for a heap */

int heapInit(struct heap_t *pThis, size_t tSize, size_t cap, int (*gt)(const void *, const void*));
/* initialize pThis: set the size per object as tSize,
 * the capacity as cap,
 * the comparison function as gt: 
 *     gt(a,b) returns -1 if a<b
 *     gt(a,b) returns  0 if a=b
 *     gt(a,b) returns  1 if a>b
 * Return 0 for normal execution.
 * Bonus: Using dynamic capacity when cap=0.  
 */

int heapPush(struct heap_t *pThis, const void *pObj);
/* Push the object into the heap.
 * Return 0 for normal execution.
 */

int heapPop(struct heap_t *pThis, void *pRet);
/* Pop the max object from the heap.
 * Write the result to *pRet.
 * Return 0 for normal execution.
 */

int heapEmpty(struct heap_t *pThis);
/* return non-zero if the heap is empty */

int heapTop(struct heap_t *pThis, void *pRet);
/* Write the top (max) object of the heap.
 * Return 0 for normal execution.
 */

size_t heapCap(struct heap_t *pThis);
/* Returns the actual capacity. */

size_t heapSize(struct heap_t *pThis);
/* Returns the size of heap; */

size_t heapTypeSize(struct heap_t *pThis);
/* Returns the size of the objects in the heap */ 

int heapFree(struct heap_t *pThis);
/* Release the memeory. 
 * Return 0 for normal execution.
 */

#endif
