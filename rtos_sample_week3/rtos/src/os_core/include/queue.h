#ifndef __QUEUE_H__
#define __QUEUE_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct node {
   struct node *prev;
   struct node *next;
} node_t;


typedef struct queue {
       node_t headNode;
} queue_t;


inline void vQueue_Init(queue_t *pxQueue);
inline node_t * pxQueue_First_Node(queue_t *pxQueue);
inline node_t * pxQueue_Last_Node(queue_t *pxQueue);
inline void vQueue_Append_Node(queue_t *pxQueue, node_t *pxNode);
inline void vQueue_Push_Node(queue_t *pxQueue, node_t *pxNode);
inline void vNode_Remove(node_t *pxNode);
inline node_t * pxQueue_Head_Node(queue_t *pxQueue);
inline node_t * pxQueue_Remove_First_Node(queue_t *pxQueue);
inline node_t * pxQueue_Remove_Last_Node(queue_t *pxQueue);
inline void vNode_Insert(node_t *pxPrevNode, node_t *pxNewNode);

#ifdef __cplusplus
} //extern "C"
#endif
#endif 

