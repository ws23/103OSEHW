#ifndef __PROJDEFS_H__
#define __PROJDEFS_H__

#ifdef __cplusplus
extern "C"
{
#endif


#define U32 unsigned long
#define U16 unsigned short
#define U8  unsigned char
#define S32 long
#define S16 short
#define	S8  char
#define Size_t	unsigned short
#define BYTE	unsigned char

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



