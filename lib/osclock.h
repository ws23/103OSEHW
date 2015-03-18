#ifndef __OSCLOCK_H__
#define __OSCLOCK_H__
 
#ifdef __cplusplus
extern "C"
{
#endif 
 
#include "projdefs.h"

#define MAXLOWTICK	0xFFFFFFFF
typedef struct osTick {
	U32 High;
	U32 Low;
} osTick_t;

inline void vTick_Inc(osTick_t *pxDest, osTick_t *pxSource, U32 amount);
inline void vOsTick_Init();
inline osTick_t * pxGet_Current_Tick();
inline S8 scCompare_Tick(osTick_t *pxTimer1, osTick_t *pxTimer2);

#ifdef __cplusplus
}//extern "C"
#endif

#endif