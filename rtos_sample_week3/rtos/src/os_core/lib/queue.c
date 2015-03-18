#include "../include/system.h"
 
inline void vQueue_Init(queue_t *pxQueue){
   pxQueue->headNode.next = &(pxQueue->headNode);
   pxQueue->headNode.prev = &(pxQueue->headNode);
}

inline node_t * pxQueue_Head_Node(queue_t *pxQueue){
   return (node_t*)&pxQueue->headNode;
}


inline node_t * pxQueue_First_Node(queue_t *pxQueue){
   return pxQueue->headNode.next;
}

inline node_t * pxQueue_Last_Node(queue_t *pxQueue){
   return pxQueue->headNode.prev;
}

/* Append pxNode to pxQueue. pxNode becomes the last node of pxQueue */
inline void vQueue_Append_Node(queue_t *pxQueue, node_t *pxNode) {
   node_t *q;
                        
   q = pxQueue_Last_Node(pxQueue);                  
   q->next    		= pxNode;
   pxNode->next 	= &(pxQueue->headNode);
   pxNode->prev 	= q;
   pxQueue->headNode.prev 	= pxNode; 
}

/* add pxNode to the first node of pxQueue */ 
inline void vQueue_Push_Node(queue_t *pxQueue, node_t *pxNode) {
   node_t *q;
                        
   q = &(pxQueue->headNode);                  
   q->prev     		= pxNode;
   pxNode->next  	= q;
   pxNode->prev  	= &(pxQueue->headNode);
   pxQueue->headNode.next 	= pxNode;
}


/*
*  Remove a node from a queue
*/
inline void vNode_Remove(node_t *pxNode) {
   node_t *q;
    
   q = pxNode->prev;
   if (q->prev != pxNode) {//queue has only one headNode element
		q->next = pxNode->next;
		pxNode->next->prev = q;
		pxNode->next = NULL;
		pxNode->prev = NULL;
   }     
}

/*
* Remove first node from pxQueue
*/
inline node_t * pxQueue_Remove_First_Node(queue_t *pxQueue) {
   node_t *q;
                        
   q = pxQueue_First_Node(pxQueue);                  
   if (q != &(pxQueue->headNode)) {
       vNode_Remove(q);
   }    
   return q;
}

/*
* Remove last node from pxQueue
*/
inline node_t * pxQueue_Remove_Last_Node(queue_t *pxQueue) {
   node_t *q;
                        
   q = pxQueue_Last_Node(pxQueue);                  
   if (q != &(pxQueue->headNode)) {
       vNode_Remove(q);
   }    
   return q;
}

/*
*  append pxNewNode to next of pxPrevNode
*/
inline void vNode_Insert(node_t *pxPrevNode, node_t *pxNewNode) {
   pxNewNode->next 			= pxPrevNode->next;
   pxPrevNode->next 		= pxNewNode;
   pxNewNode->next->prev 	= pxNewNode;
   pxNewNode->prev 			= pxPrevNode;
}


