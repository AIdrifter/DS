#ifndef __ds__disj__header__
#define __ds__disj__header__

#define __DS__DISJ__NORMAL__       0x00000000
#define __DS__DISJ__SAMESET__      0x00000001
#define __DS__DISJ__DIFFSET__      0x00000002
#define __DS__DISJ__OUT_OF_MEM__	0x00000004

struct disj_t;

struct disj_t* disjAlloc( );

int disjInit( struct disj_t *pThis , size_t size );
/* initialize *pThis to {{0}, {1}, ..., {size-1}}.
 * Return 0=__DS__DISJ__NORMAL__ if initialization ends normally
 * Return __DS__DISJ__OUT_OF_MEM__ if there is not enough memory
 */

int disjUnion( struct disj_t *pThis , const long obj1 , const long obj2 );
/* Union two sets p1 and p2 where obj1 is in p1 and obj2 is in p2
 * Return __DS__DISJ__DIFFSET__ if p1 was not p2 before union
 * Return __DS__DISJ__SAMESET__ if p1 was p2 before union
 */

long disjFind( struct disj_t *pThis , const long obj );
/* Return the representative of the set to which obj belongs
 * Bonus : Find with compression
 */

int disjSameSet( struct disj_t *pThis , const long obj1 , const long obj2 );
/* Test whether obj1 and obj2 are in the same set
 * Return __DS__DISJ__DIFFSET__ if obj1 and obj2 are in different sets
 * Return __DS__DISJ__SAMESET__ if obj1 and obj2 are in the same set
 */

size_t disjSetSize( struct disj_t *pThis , const long obj );
/* Return the size of set contains obj. */

size_t disjSize( struct disj_t *pThis );
/* Return the size of the universe/ground set */

int disjFree(struct disj_t *pThis);
/* Release the memory 
 * Return 0 for normal execution.
 */

#endif