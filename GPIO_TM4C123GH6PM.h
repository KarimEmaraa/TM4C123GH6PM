#ifndef __GPIO_TM4C123GH6PM_H
#define __GPIO_TM4C123GH6PM_H

#include <stdbool.h>
#include "TM4C123GH6PM.h"


#if defined (__CC_ARM)
  #define __FORCE_INLINE  static __forceinline
#else
  #define __FORCE_INLINE  __STATIC_INLINE
#endif
	
/// GPIO Pin identifier 
typedef struct _GPIO_PIN_ID {
	GPIOA_Type * port;
	uint8_t num;
}GPIO_PIN_ID;

/// Port Direction
typedef enum {
	GPIO_DIR_INPUT = 0x00,
	GPIO_DIR_OUTPUT = 0x01,
}GPIO_DIR;

typedef enum
{
	GPIO_OUT_STRENGTH_2MA,
	GPIO_OUT_STRENGTH_4MA,
	GPIO_OUT_STRENGTH_8MA,
	GPIO_OUT_SLEWRATE,
	GPIO_OUT_OPEN_DRAIN,

	GPIO_ALTERNATE,
	
	GPIO_IN_PULL_UP,
	GPIO_IN_PULL_DOWN,
	
}GPIO_MODE;

/**
	\brief 		Enable Clock to the GPIO Pad
	\GPIOx 		pointer to GPIO pad
	\enable 	true enables clock, false disables clock
	\return 	void
*/
void GPIO_PortClock(GPIOA_Type *GPIOx, bool enable);

/**
	\brief 		Gets GPIO port clock state
	\GPIOx 		pointer to GPIO pad
	\return 	true if clock is enable otherwise false
*/
bool GPIO_GetPortClockState (GPIOA_Type *GPIOx);

/**
	\brief 		Configures PORT pad
	\GPIOx 		pointer to GPIO pad
	\num 			port pin number
	\dir 			pin direction \ref GPIO_DIR
	\mode 		pin modes \ref GPIO_MODE
	\return 	true if suecces, false otherwise
	\note     returns false on pins that requires commit control process.
*/
bool GPIO_PinConfigure(GPIOA_Type		     *GPIOx,
                       uint32_t           num,
                       GPIO_MODE          mode,
											 GPIO_DIR           dir);

/**
	\brief 		write to port pin
	\GPIOx		pointer to GPIO pad
	\num 			port bit number
	\val			value to be written (0 or 1)
	\return 	void
*/
__FORCE_INLINE void GPIO_PinWrite (GPIOA_Type *GPIOx, uint8_t num, uint32_t val){
	(*(volatile uint32_t *)((uint32_t)GPIOx + (4 * (1U << num)))) =  val << num;
}

/**
	\brief		Read a port pin
	\GPIOx 		Pointer to GPIO pad
	\num			Port bit number \ref GPIO_PIN
	\return		Pin value(NON zero value or 0)
*/
__FORCE_INLINE uint32_t GPIO_PinRead (GPIOA_Type *GPIOx, uint8_t num) {
  return (*(volatile uint32_t *)((uint32_t)GPIOx + (4 * (1U << num))));
}	

/**
	\brief		Write to port pins
	\GPIOx 		Pointer to GPIO pad
	\mask			Selected pins
	\val			Pins values
	\return 	void
*/
__FORCE_INLINE void GPIO_PortWrite (GPIOA_Type *GPIOx, uint16_t mask, uint16_t val) {
  GPIOx->DATA = (GPIOx->ODR & ~mask) | val;
}

/**
	\brief		Read port pins
	\GPIOx 		Pointer to GPIO pad
	\return 	port pin values
*/
__FORCE_INLINE uint16_t GPIO_PortRead (GPIOA_Type *GPIOx) {
  return (GPIOx->DATA);
}
	
	


#endif
