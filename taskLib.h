/*
 * taskLib.h
 *
 * Created: 12/3/2015 0:44:10
 *  Author: chtsai
 */ 


#ifndef TASKLIB_H_
#define TASKLIB_H_

#include "projdefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

U16		usNew_Task_Id();
task_t *pxGet_Ready_Task(U16 priority);
S8		ucGet_Highest_Prio(void);
void	vSet_Current_Task(task_t *pxTask);
task_t *pxGet_Current_Task(void);

#ifdef __cplusplus
}
#endif
#endif /* TASKLIB_H_ */