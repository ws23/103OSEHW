#include <system.h>

volatile osTick_t xCurrentTick; //tick is change in ISR

inline osTick_t * pxGet_Current_Tick(void) {
    return (osTick_t*)&xCurrentTick;
}

/*
pxDest = pxSource + amount
*/
inline void vTick_Inc(osTick_t *pxDest, osTick_t *pxSource, U32 amount) {
     
     pxDest->Low  =  pxSource->Low + amount;
     pxDest->High =  pxSource->High; 

     if (MAXLOWTICK - pxSource->Low < amount) 
     pxDest->High++;
}

/* return 1: t1>t2, -1:t1<t2, 0:t1=t2 */ 
S8 scCompare_Tick(osTick_t *pxTimer1, osTick_t *pxTimer2) {
	S8 scReturnValue=0;
	U32 High1 = pxTimer1->High;
	U32 High2 = pxTimer2->High;
	U32 Low1 = pxTimer1->Low;
	U32 Low2 = pxTimer2->Low;

    if (High1 > High2) scReturnValue = 1;     
	if (High1 < High2) scReturnValue = -1;     
    if (Low1 > Low2)   scReturnValue = 1;     
    if (Low1 < Low2)   scReturnValue = -1;     
    return scReturnValue;
/*	
    if (pxTimer1->High > pxTimer2->High) scReturnValue = 1;     
	if (pxTimer1->High < pxTimer2->High) scReturnValue = -1;     
    if (pxTimer1->Low > pxTimer2->Low)   scReturnValue = 1;     
    if (pxTimer1->Low < pxTimer2->Low)   scReturnValue = -1;     
    return scReturnValue;
*/	
}


inline void vOsTick_Init(void)
{
     
      xCurrentTick.Low = 0;
      xCurrentTick.High = 0;
	  vOsTimer_Hardware_Setup();
}
