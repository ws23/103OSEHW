#include <system.h>

queue_t xAlarmClockQueue;

static void vSystem_Queue_Initial(void) {

	vQueue_Init(&xAlarmClockQueue);
}

void vKernel_Initial(void) {
	vDisable_Interrupts();

	vSystem_Queue_Initial();
	vOsTick_Init();
	
}
