#ifndef __ALARMCLOCK_H__
#define __ALARMCLOCK_H__

#include "projdefs.h"


#ifdef __cplusplus
extern "C"
{
#endif

// flag bit 0: activated or deactivated
// flag bit 1: periodic or oneshot
#define ACTIVATED 	( 0x1 )
#define PERIODIC	( 0x01 << 1 )  // bit 1=1, bit 1=0 ONESHOT


typedef enum {
	SET_TIME=0,
	GET_TIME,
	SET_ONESHOT,
	SET_PERIODIC
} ALARM_CLOCK_CMD_TYPE;

/*
 * timer structure
 */
typedef struct alarmClock {
	node_t 	 node;										/* the node of timer list. 					*/
	char 	 name[configMAX_TASK_NAME_LEN];
	U8	     flag;									    /*0 bit:actived, 1 bit:periodic or oneshot	*/
	void 	 (*timeoutFunc)(void* parameter);			/* timeout function. 						*/
	void 	 *parameter;								/* timeout function's parameter. 			*/
	U32 	 initTick;									/* inital ticks.	 						*/
	osTick_t timeoutTick;								/* timeout tick. 							*/
} alarmClock_t;


void 	vAlarmClock_Init(alarmClock_t *pxTimer, const char* name, 
						 void (*timeoutFunc)(void* parameter), void* parameter, 
						 U32 initTime, ALARM_CLOCK_CMD_TYPE flag);
alarmClock_t* pxAlarmClock_Create(const char* name, void (*timeoutFunc)(void* parameter), 
								  void* parameter, U32 initTime, ALARM_CLOCK_CMD_TYPE flag);
U8 		ucAlarmClock_Start(alarmClock_t* pxTimer);
void 	vAlarmClock_Stop(alarmClock_t* pxTimer);
U32 	ulAlarmClock_Control(alarmClock_t* pxTimer, ALARM_CLOCK_CMD_TYPE cmd, U32 arg);
U8 		ucAlarmClock_Delete(alarmClock_t* pxTimer);
void 	vAlarmClock_Check(void);

#ifdef __cplusplus
}
#endif
#endif
