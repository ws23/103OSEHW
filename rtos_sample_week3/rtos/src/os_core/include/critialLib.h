#ifndef __CRITICALLIB_H__
#define __CRITICALLIB_H__
#include "projdefs.h"
inline U8 ucEnter_Critical(void);
inline void vExit_Critical(U8);
inline void vDisable_Interrupts(void);
inline void vEnable_Interrupts(void);
#endif
