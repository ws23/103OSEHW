#include <system.h>

/* enable and disable all interrupts */
inline void vDisable_Interrupts(void) {
	asm volatile ( "cli" :: );
}

inline void vEnable_Interrupts(void) {
	asm volatile ( "sei" :: );
}

/* Critical section management. */
/*
inline void vEnter_Critical(void) {
	asm volatile ( "in		__tmp_reg__, __SREG__" :: );
	asm volatile ( "push	__tmp_reg__" :: );
	asm volatile ( "cli" :: );								
}

inline void vExit_Critical(void) {
	asm volatile ( "pop		__tmp_reg__" :: );		
	asm volatile ( "out		__SREG__, __tmp_reg__" :: );	
}
*/

inline U8 ucEnter_Critical(void) {
	U8 sreg;
	sreg = SREG;
	vDisable_Interrupts();
	return sreg;
}

inline void vExit_Critical(U8 sreg) {
	SREG = sreg;
}


