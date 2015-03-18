#include <system.h>
#include <string.h>

extern queue_t xAlarmClockQueue;


void vAlarmClock_Init(alarmClock_t *pxAlarmClock, const char* name, 
           void (*timeoutFunc)(void* parameter), void* parameter, 
           U32 initTime, ALARM_CLOCK_CMD_TYPE flag) {
	
	switch (flag) {
		case SET_ONESHOT:
			pxAlarmClock->flag &= ~PERIODIC;       //clear bit 1
			break;
		case SET_PERIODIC:
			pxAlarmClock->flag |= PERIODIC;    // set bit 1
			break;
		default:
			break;
	}	
	/* set deactivated  and  one-shot*/	
	pxAlarmClock->node.prev 		= NULL;
	pxAlarmClock->node.next			= NULL;
	strcpy(pxAlarmClock->name, name);
	pxAlarmClock->flag        		&= ~ACTIVATED;          //clear bit 0: deactivated
	pxAlarmClock->timeoutFunc  		= timeoutFunc;
	pxAlarmClock->parameter   		= parameter;
	pxAlarmClock->timeoutTick.Low	= 0;
	pxAlarmClock->timeoutTick.High	= 0;
	pxAlarmClock->initTick 			= initTime;
}

/**
 * This function will create a AlarmClock for pointer variable
 *
 */
alarmClock_t* pxAlarmClock_Create(const char* name, void (*timeoutFunc)(void* parameter), 
					  void* parameter, U32 initTime, ALARM_CLOCK_CMD_TYPE flag) {   
	alarmClock_t *pxReturnAlarmClock = (alarmClock_t*) pvMalloc(sizeof(alarmClock_t));
	if (pxReturnAlarmClock == NULL) return NULL;
	
	vAlarmClock_Init(pxReturnAlarmClock, name, timeoutFunc, parameter, initTime, flag);
	return pxReturnAlarmClock;
}


/**
 * This function will start the AlarmClock
 */
U8 ucAlarmClock_Start(alarmClock_t* pxAlarmClock) {

	alarmClock_t *pxCurrentNode,*pxLastNode;
	U8 flagReg;
	

	if (pxAlarmClock->flag & ACTIVATED || pxAlarmClock == NULL) return FAIL; //AlarmClock is start, can not start again


	/* get timeout tick, which will wrap around if it reaches max ticks */
	vTick_Inc(&pxAlarmClock->timeoutTick, pxGet_Current_Tick(), pxAlarmClock->initTick);

    
	flagReg = ucEnter_Critical();
	/* insert AlarmClock to system AlarmClock list */
 	pxCurrentNode = (alarmClock_t *)pxQueue_First_Node(&xAlarmClockQueue);
 	pxLastNode = (alarmClock_t *)pxQueue_Head_Node(&xAlarmClockQueue);
	vNode_Remove((node_t *) pxAlarmClock);
		
	/* found suitable position in AlarmClock list */
	while(pxCurrentNode != pxLastNode) {
		if (scCompare_Tick(&(pxCurrentNode->timeoutTick), &(pxAlarmClock->timeoutTick))==1) {
			vNode_Insert(((node_t *)pxCurrentNode)->prev, (node_t *)pxAlarmClock);
			break;
		} else {
		   pxCurrentNode = (alarmClock_t *)((node_t *)pxCurrentNode)->next;
		}
	}
	if (pxCurrentNode == pxLastNode) vQueue_Append_Node(&xAlarmClockQueue, (node_t *) pxAlarmClock);
	
	pxAlarmClock->flag |= ACTIVATED;
    vExit_Critical(flagReg);
	return PASS;
}

/**
 * This function will stop the AlarmClock
 */
void vAlarmClock_Stop(alarmClock_t* pxAlarmClock) {
                    
	if(!(pxAlarmClock->flag & ACTIVATED)) return;   //AlarmClock is noactived now

	/* change state to deactivated */
	pxAlarmClock->flag &= ~ACTIVATED;

	/* remove it from AlarmClock list */
	U8 flagReg = ucEnter_Critical();
	vNode_Remove((node_t *) pxAlarmClock);
	vExit_Critical(flagReg);
}

/**
 * This function will get or set some options of the AlarmClock
 */
U32 ulAlarmClock_Control(alarmClock_t* pxAlarmClock, ALARM_CLOCK_CMD_TYPE cmd, U32 arg) {
	switch (cmd)	{
	case SET_TIME:
		pxAlarmClock->initTick = arg;
		break;
	case GET_TIME:
		return pxAlarmClock->initTick;
	case SET_ONESHOT:
		pxAlarmClock->flag &= ~PERIODIC;
		break;
	case SET_PERIODIC:
		pxAlarmClock->flag |= PERIODIC;
		break;
	}
	return PASS;
}


/**
 * This function will delete a AlarmClock and release AlarmClock memory
 *
 */
U8 ucAlarmClock_Delete(alarmClock_t* pxAlarmClock) {
    
    if (pxAlarmClock ==  NULL) return FAIL;

	/* remove it from AlarmClock list */
	U8 flagReg = ucEnter_Critical();
	vNode_Remove((node_t *) pxAlarmClock);
    vExit_Critical(flagReg);
    vFree(pxAlarmClock);
	return PASS;
}


/**
 * This function will check AlarmClock list, if a timeout event happens, the
 * corresponding timeout function will be invoked.
 *
 */

void vAlarmClock_Check(void) {
	alarmClock_t	*pxCurrentNode, *pxLastNode;
	osTick_t *pxTick,*pxCurrentNodeTick;
	U8 flagReg;
	
	
	pxCurrentNode = (alarmClock_t *)pxQueue_First_Node(&xAlarmClockQueue);
	pxLastNode = (alarmClock_t *)pxQueue_Head_Node(&xAlarmClockQueue);
	while (pxCurrentNode != pxLastNode) {
          pxTick = pxGet_Current_Tick();  
		  pxCurrentNodeTick = (osTick_t*)&pxCurrentNode->timeoutTick;
		  if (scCompare_Tick(pxTick, pxCurrentNodeTick) >=0) {
				flagReg = ucEnter_Critical();
				vNode_Remove((node_t *)pxCurrentNode);
				vExit_Critical(flagReg);
				/// call timeout function 
				pxCurrentNode->timeoutFunc(pxCurrentNode->parameter);

				if ((pxCurrentNode->flag & PERIODIC) && (pxCurrentNode->flag & ACTIVATED)) {  //periodic AlarmClock
					// restart it 
					pxCurrentNode->flag &= ~ACTIVATED;
					ucAlarmClock_Start(pxCurrentNode);
				} else {
					// stop AlarmClock 
					pxCurrentNode->flag &= ~ACTIVATED;
				}
				//next AlarmClock
				pxCurrentNode = (alarmClock_t *)(((node_t *)pxCurrentNode)->next);
			}
			else break;
		}
}

