#include <system.h>
#include <projdefs.h>

extern volatile osTick_t xCurrentTick;

ISR(TIMER5_COMPA_vect)
{
	vTick_Inc((osTick_t*)&xCurrentTick, (osTick_t*)&xCurrentTick, 0x1);
	vAlarmClock_Check();
	/* TODO (#1#): 
			   1. check schedule
	*/                                
}

/*
 * Setup timer 5 compare match A to generate a tick interrupt.
 */
void vOsTimer_Hardware_Setup(void) {
U32 ulCompareMatch;

	/* Using 16bit timer 1 to generate the tick.  Correct fuses must be
	selected for the configCPU_CLOCK_HZ clock. */

	ulCompareMatch = configCPU_CLOCK_HZ / configTICK_RATE_HZ;

	/* We only have 16 bits so have to scale to get our required tick rate. */
	ulCompareMatch /= configCLOCK_PRESCALER;

	/* Adjust for correct value. because count from 0*/
	ulCompareMatch -= ( U32 ) 1;

	//clear relative register
	vDisable_Interrupts();
	TCCR5A 	= 0;
	TCCR5B 	= 0;
	TCNT5	= 0;
	/* Setup compare match value for compare match A.  Interrupts are disabled 
	before this is called so we need not worry here. */

	OCR5A = ulCompareMatch; 	// compare match register

	/* Setup clock source and compare match behaviour. */
	TCCR5B |= (1 << WGM52);		// CTC mode
	TCCR5B |= (1 << CS52);		// 256 prescaler

	TIMSK5 = (1 << OCIE5A);		// enable timer compare interrupt
	vEnable_Interrupts();		// enable all interrupts
}
