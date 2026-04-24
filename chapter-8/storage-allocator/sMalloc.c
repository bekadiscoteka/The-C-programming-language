#include "sMalloc.h"
#include <stdio.h>
#define NALLOC 1024 /* minimum #units to request */

#define DIVMASK_HEADER ( ( 0UL - 1 ) - ( sizeof(Header) - 1 ))

static Header *morecore(unsigned);
static Header base;         /* empty list to get started */
static Header *freep = NULL; /* start of free list */

/* malloc: general-purpose storage allocator */
void *s_malloc(unsigned nbytes)
{
	if (nbytes == 0)
		return NULL;

    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;

    /* Calculate size in units of Header, plus one for the header itself */
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) { /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    /* Traverse the circular list looking for a block large enough */
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) { /* big enough */
            if (p->s.size == nunits) /* exactly */
                prevp->s.ptr = p->s.ptr;
            else {              /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1); /* return pointer to data (after header) */
        }
        if (p == freep) /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL)
                return NULL; /* none left */
    }
}

void *s_calloc(unsigned n, unsigned size) {
	unsigned nbytes;

	if (size == 0 || n == 0)
		return NULL;

	if (__builtin_mul_overflow(n, size, &nbytes))
		return NULL;

	return s_malloc( nbytes );
}


/* morecore: ask system for more memory */
static Header *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1) /* no space at all */
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    s_free((void *)(up+1));
    return freep;
}

/* free: put block ap in free list */
void s_free(void *ap)
{
	if (ap == NULL) {
		fprintf(stderr, "pointer is empty\n");
		return;
	}

    Header *bp, *p;

    bp = (Header *)ap - 1; /* point to block header */

	if (bp->s.size == 0) {
		fprintf(stderr, "pointer %p corrupter\n", bp);
		return;
	}

    /* Find the spot in the list to insert the block */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; /* freed block at start or end of arena */

    if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }

    if (p + p->s.size == bp) {         /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }
    
    freep = p;
}

void s_bfree(void *cp, unsigned size) {
	if (size <= (sizeof(Header) * 2)){ 
		fprintf(stderr, "%s", "not enough space\n");
		return;
	}

	/* alignment check */
	
	if ( (( unsigned long )cp % sizeof(Header)) != 0 ) {
		fprintf(stderr, "%s", "space alignment issues, not all memory will be exploited\n");
		void* newptr = DIVMASK_HEADER & ((unsigned long) cp + sizeof(Header));
		if (newptr < cp + size)
			s_bfree(newptr, (cp + size) - newptr);
		return;
	}


	Header *hp = cp;

	hp->s.size = size / sizeof(Header);
	hp->s.ptr = hp+1;

	s_free(hp->s.ptr);
}





