#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>


#include "queue.h"
#include "heap.h"
#include "osclock.h"
#include "critialLib.h"
#include "timerSetup.h"
#include "alarmClock.h"
#include "kernelStart.h"


#ifdef __cplusplus
}//extern "C"
#endif
#endif /*__SYSTEM_H__*/

