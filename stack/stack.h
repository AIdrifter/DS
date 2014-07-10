#ifndef __ds__stack__header__
#define __ds__stack__header__



#define __DS__STACK__NORMAL__		0x00000000
#define __DS__STACK__FULL__			0x00000001
#define __DS__STACK__EMPTY__		0x00000002
#define __DS__STACK__OUT_OF_MEM__	0x00000004

struct stack_t;
/* Stacks store various but fixed-size data */

struct stack_t *stackAlloc();
/* Allocate memory for a stack. Return a pointer */

int stackInit(struct stack_t *pThis, size_t tSize, size_t cap);
/* initialize pThis: set the size per object as tSize
 * and the capacity as cap.
 * Return 0 for normal execution.
 * Bonus: Using dynamic capacity when cap=0.  
 */

int stackPush(struct stack_t *pThis, const void *pObj);
/* Push the object into the stack.
 * Return 0 for normal execution.
 */

int stackPop(struct stack_t *pThis, void *pRet);
/* Pop the top object from the stack.
 * Write the result to *pRet.
 * Return 0 for normal execution.
 */

int stackEmpty(struct stack_t *pThis);
/* return non-zero if the stack is empty */

int stackTop(struct stack_t *pThis, void *pRet);
/* Write the top object of the stack.
 * Return 0 for normal execution.
 */

size_t stackCap(struct stack_t *pThis);
/* Returns the actual capacity. */

size_t stackSize(struct stack_t *pThis);
/* Returns the size of stack */

size_t stackTypeSize(struct stack_t *pThis);
/* Returns the size of the objects in the stack */ 

int stackFree(struct stack_t *pThis);
/* Release the memeory. 
 * Return 0 for normal execution.
 */




#endif
