#ifndef __PROJDEFS_H__
#define __PROJDEFS_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef unsigned long U32; 
typedef unsigned short U16; 
typedef unsigned char U8; 
typedef long S32; 
typedef short S16; 
typedef char S8; 
typedef unsigned Size_t; 
typedef unsigned char BYTE; 

#define TRUE 	(1)   
#define FALSE 	(0)
#define NULL    ((void *)0)
#define PASS	(1)
#define FAIL	(0)

#define configCPU_CLOCK_HZ			( ( U32 ) F_CPU )
#define configTICK_RATE_HZ			( 100 )
#define configCLOCK_PRESCALER		( 256 )
#define configMINIMAL_STACK_SIZE	( ( Size_t ) 85 )
#define configTOTAL_HEAP_SIZE		( 4096 )
#define configMAX_TASK_NAME_LEN		( 16 )


#ifdef __cplusplus
}//extern "C"
#endif
#endif /* __PROJDEFS_H__ */



