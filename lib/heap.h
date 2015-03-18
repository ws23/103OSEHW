#ifndef __HEAP_H__
#define __HEAP_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "projdefs.h"

/* Define the linked list structure.  This is used to link free blocks in order
of their size. */
typedef struct xBlockLink 
{
	struct xBlockLink *pxNextFreeBlock;	/*<< The next free block in the list. */
	Size_t size;						/*<< The size of the free block. */
} xBlockLink_t;

void *pvMalloc(Size_t xWantedSize);
void vFree( void *pvCurrentBlock );

#ifdef __cplusplus
}//extern "C"
#endif
#endif