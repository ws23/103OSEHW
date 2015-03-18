/*
 * testMain.c
 *
 * Created: 9/3/2015 19:57:03
 *  Author: chtsai
 */ 
#include <rtos.h>

alarmClock_t *alarm1, *alarm2;
int x;

void alarmTimeOut(void *p) {
	x++;
}



void setup(){
	x=0;
	alarm1 = (alarmClock_t *)pvMalloc(sizeof(alarmClock_t));
	alarm2 = (alarmClock_t *)pvMalloc(sizeof(alarmClock_t));
	vAlarmClock_Init(alarm1,"alarm1", alarmTimeOut, alarm1, 50, SET_ONESHOT);
	vAlarmClock_Init(alarm2,"alarm2", alarmTimeOut, alarm2, 60, SET_PERIODIC);
	ucAlarmClock_Start(alarm1);
	ucAlarmClock_Start(alarm2);
}

void loop(){
	
}