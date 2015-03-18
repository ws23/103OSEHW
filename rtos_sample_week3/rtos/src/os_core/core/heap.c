#include <stdlib.h>
#include <system.h>

BYTE ucHeap[ configTOTAL_HEAP_SIZE ];


const Size_t  heapSTRUCT_SIZE = sizeof( xBlockLink_t );
#define heapMINIMUM_BLOCK_SIZE	( ( Size_t ) ( heapSTRUCT_SIZE * 2 ) )
xBlockLink_t xStart;

//sem_t heapSem;
static void vInsert_Block_Into_Heap( xBlockLink_t *pxBlockToInsert ) {																				
	xBlockLink_t *q,*p;																
	Size_t size;																	
																					
	size = pxBlockToInsert->size;										
	/* Iterate through the list until a block is found that has a larger size */	
	/* than the block we are inserting. */		
	q = xStart.pxNextFreeBlock;
	p = &xStart;
	while(q && q->size < size) {
		p = q;
		q = q->pxNextFreeBlock;
	}
																					
	/* Update the list to include the block being inserted in the correct */		
	/* position. */																	
	pxBlockToInsert->pxNextFreeBlock = q;					
	p->pxNextFreeBlock = pxBlockToInsert;									
}

static void vHeap_Init() {
	xBlockLink_t *pxFirstFreeBlock;
	
	pxFirstFreeBlock 					= (xBlockLink_t *)ucHeap;
	pxFirstFreeBlock->size 				= configTOTAL_HEAP_SIZE;
	pxFirstFreeBlock->pxNextFreeBlock 	= NULL;
	xStart.pxNextFreeBlock 				= pxFirstFreeBlock;
	xStart.size      					= 0;
//	initial mutex or a semaphore
}

void *pvMalloc(Size_t xWantedSize) {
	static char xHeapHasBeenInitialised = FALSE;
	void *pvReturnBlock = NULL;	
	xBlockLink_t *pxPrevBlock, *pxCurrentBlock;
	xBlockLink_t *pxNewBlock;

	//first call vMalloc
	if (!xHeapHasBeenInitialised) {
		vHeap_Init();
		xHeapHasBeenInitialised = TRUE;
	}
	
	if (!xWantedSize) return pvReturnBlock; //wanted size 0 
	
	Size_t size = xWantedSize + sizeof(xBlockLink_t);

    // critical region
	// take a semaphore
	pxPrevBlock = &xStart;
	pxCurrentBlock = xStart.pxNextFreeBlock;
	while ((pxCurrentBlock) && (pxCurrentBlock->size < size)) {
		pxPrevBlock = pxCurrentBlock;
		pxCurrentBlock = pxCurrentBlock->pxNextFreeBlock;
	}	
	
	if (pxCurrentBlock) {
		pvReturnBlock = (void *)((BYTE *)pxCurrentBlock + heapSTRUCT_SIZE);
		pxPrevBlock->pxNextFreeBlock = pxCurrentBlock->pxNextFreeBlock;
		
		if (pxCurrentBlock->size > size+heapMINIMUM_BLOCK_SIZE) {
			//split block into two blocks
			pxNewBlock = ( void * ) ( ( BYTE * ) pxCurrentBlock + size );

			/* Calculate the sizes of two blocks split from the single
			block. */
			pxNewBlock->size = pxCurrentBlock->size - size;
			pxCurrentBlock->size = size;

			/* Insert the new block into the list of free blocks. */
			vInsert_Block_Into_Heap(pxNewBlock);
		}
	}
	//critical region
	//release a semaphore
	return pvReturnBlock;
}

void vFree( void *pvCurrentBlock ) {
	BYTE *pxCurrentBlock = ( BYTE * ) pvCurrentBlock;

	if( pvCurrentBlock )
	{
		/* The memory being freed will have an xBlockLink structure immediately
		before it. */
		pxCurrentBlock = pxCurrentBlock - heapSTRUCT_SIZE;

		//critical region
		//take semaphore
		/* Add this block to the list of free blocks. */
		vInsert_Block_Into_Heap( ( ( xBlockLink_t * ) pxCurrentBlock ) );
		//release semaphore;
	}
}
