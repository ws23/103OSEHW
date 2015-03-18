#include "queue.h"

inline void vQueue_Init(queue_t *pxQueue){
	pxQueue->headNode.prev = pxQueue->headNode; 
	pxQueue->headNode.next = pxQueue->headNode; 	
}

inline node_t * pxQueue_First_Node(queue_t *pxQueue){
	return pxQueue->headNode.next; 
}

inline node_t * pxQueue_Last_Node(queue_t *pxQueue){
	return pxQueue->headNode.prev; 	
}

inline void vQueue_Append_Node(queue_t *pxQueue, node_t *pxNode){
	node_t *first = pxQueue_First_Node(pxQueue); 
	first->prev = pxNode; 
	pxQueue->headNode.next = pxNode; 
	pxNode->prev = pxQueue->headNode; 
	pxNode->next = first; 
}

inline void vQueue_Push_Node(queue_t *pxQueue, node_t *pxNode){
	node_t *last = pxQueue_Last_Node(pxQueue);
	last->next = pxNode; 
	pxQueue->headNode.prev = pxNode; 
	pxNode->prev = last; 
	pxNode->next = pxQueue->headNode; 
}

inline void vNode_Remove(node_t *pxNode){
	pxNode->prev->next = pxNode->next; 
	pxNode->next->prev = pxNode->prev; 
	free(pxNode); 
}

inline node_t * pxQueue_Head_Node(queue_t *pxQueue){
	return pxQueue->headNode; 
}

inline node_t * pxQueue_Remove_First_Node(queue_t *pxQueue){
	node_t *first = pxQueue_First_Node(pxQueue); 
	pxQueue->headNode.next = first->next; 
	first->next->prev = pxQueue->headNode;
	free(first);
	return pxQueue->headNode.next; 
}

inline node_t * pxQueue_Remove_Last_Node(queue_t *pxQueue){
	node_t *last = pxQueue_Last_Node(pxQueue); 
	pxQueue->headNode.prev = last->prev; 
	last->prev->next = pxQueue->headNode; 
	free(last); 
	return pxQueue->headNode.prev; 
}

inline void vNode_Insert(node_t *pxPrevNode, node_t *pxNewNode){
	pxNewNode->prev = pxPrevNode; 
	pxNewNode->next = pxPrevNode->next; 
	pxPrevNode->next = pxNewNode; 	
	pxNewNode->next->prev = pxNewNode; 
}
