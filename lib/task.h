/*
 * task.h
 *
 * Created: 10/3/2015 22:23:30
 *  Author: chtsai
 */ 


#ifndef TASK_H_
#define TASK_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "projdefs.h"

/** state of task */
typedef enum {
	READY=0,
	RUNNING,
	BLOCK,
	CLOSE
} TASK_STATE;


/** structure of Task Control Block */
typedef struct  {
    node_t              node;

	/* stack point and entry */
	void	*			pStackPtr;								/* stack pointer							*/
	void	*			pEntryPoint;							/* entry function address					*/
	void	*       	pParameter;								/* parameter for timeout					*/
	void	*       	pStackBeginAddr;						/* stack address 							*/
	Size_t 				xStackSize;								/* stack size 								*/

	U8				    ucPriority;
	U16				    usInitTick;								/* task's tick  							*/
	U16 				usRemainingTick;						/* remaining tick 							*/

	U16				    usTaskId;
	TASK_STATE 			xState;
	char				name[configMAX_TASK_NAME_LEN];
	
	alarmClock_t        alarm;
} task_t;


U8 ucTask_Init(task_t *pxTask, const char *name, void (*entry)(void* parameter),
		         void* pParameter, Size_t xStackSize, BYTE  ucPriority, U16 ulTickQuantum);

task_t * pxTask_Create (const char *name, void (*entry)(void* parameter), void* pParameter,
						Size_t xStackSize,	BYTE  ucPriority, U16 usTickQuantum);

void vTask_Resume(task_t * pxTask);
void vTask_Suspend(task_t * pxTask);
void vTask_Start(task_t *pxTask);
void vTask_Stop(void);
void vTask_Delay(U16 usDelayTick);
void vTask_Yield( void ) __attribute__ ( ( naked ) );


#ifdef __cplusplus
}
#endif

#endif /* TASK_H_ */