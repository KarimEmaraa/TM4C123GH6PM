#include "GPIO_TM4C123GH6PM.h"

void GPIO_PortClock(GPIOA_Type *GPIOx, bool enable)
{
	if(enable)
	{
		switch((uint32_t)GPIOx)
		{
			case (uint32_t)GPIOA:
			case (uint32_t)GPIOA_AHB:
				SYSCTL->RCGCGPIO |= 1;
				break;
			case (uint32_t)GPIOB:
			case (uint32_t)GPIOB_AHB:
				SYSCTL->RCGCGPIO |= 0x2;
				break;
			case (uint32_t)GPIOC:
			case (uint32_t)GPIOC_AHB:
				SYSCTL->RCGCGPIO |= 0x4;
				break;
			case (uint32_t)GPIOD:
			case (uint32_t)GPIOD_AHB:
				SYSCTL->RCGCGPIO |= 0x8;
				break;
			case (uint32_t)GPIOE:
			case (uint32_t)GPIOE_AHB:
				SYSCTL->RCGCGPIO |= 0x10;
				break;
			case (uint32_t)GPIOF:
			case (uint32_t)GPIOF_AHB:
				SYSCTL->RCGCGPIO |= 0x20;
				break;		
		}
	}
	else
	{
		switch((uint32_t)GPIOx)
		{
			case (uint32_t)GPIOA:
			case (uint32_t)GPIOA_AHB:
				SYSCTL->RCGCGPIO &= ~0x1;
				break;
			case (uint32_t)GPIOB:
			case (uint32_t)GPIOB_AHB:
				SYSCTL->RCGCGPIO &= ~0x2;
				break;
			case (uint32_t)GPIOC:
			case (uint32_t)GPIOC_AHB:
				SYSCTL->RCGCGPIO &= ~0x4;
				break;
			case (uint32_t)GPIOD:
			case (uint32_t)GPIOD_AHB:
				SYSCTL->RCGCGPIO &= ~0x8;
				break;
			case (uint32_t)GPIOE:
			case (uint32_t)GPIOE_AHB:
				SYSCTL->RCGCGPIO &= ~0x10;
				break;
			case (uint32_t)GPIOF:
			case (uint32_t)GPIOF_AHB:
				SYSCTL->RCGCGPIO &= ~0x20;
				break;		
		}
	}
}

bool GPIO_GetPortClockState (GPIOA_Type *GPIOx) 
{
		switch((uint32_t)GPIOx)
		{
			case (uint32_t)GPIOA:
			case (uint32_t)GPIOA_AHB:
				return (SYSCTL->RCGCGPIO & 0x1);
			case (uint32_t)GPIOB:
			case (uint32_t)GPIOB_AHB:
				return (SYSCTL->RCGCGPIO & 0x2);
			case (uint32_t)GPIOC:
			case (uint32_t)GPIOC_AHB:
				return (SYSCTL->RCGCGPIO & 0x4);
			case (uint32_t)GPIOD:
			case (uint32_t)GPIOD_AHB:
				return (SYSCTL->RCGCGPIO & 0x8);
			case (uint32_t)GPIOE:
			case (uint32_t)GPIOE_AHB:
				return (SYSCTL->RCGCGPIO & 0x10);
			case (uint32_t)GPIOF:
			case (uint32_t)GPIOF_AHB:
				return (SYSCTL->RCGCGPIO & 0x20);	
			default:
					return false;
		}
}

bool GPIO_PinConfigure(GPIOA_Type *GPIOx, uint32_t num, GPIO_MODE mode, GPIO_DIR dir)
{
	if(GPIO_GetPortClockState(GPIOx) == 0)
	{
		GPIO_PortClock(GPIOx, true);
	}
	/*return false on pins that requires commit control process.*/
	if(num < 4 || num == 7)
	{
		if (((uint32_t)GPIOx == GPIOC_BASE || (uint32_t)GPIOx == GPIOC_AHB_BASE) && num < 4)
			return false;
		else if(((uint32_t)GPIOx == GPIOD_BASE || (uint32_t)GPIOx == GPIOD_AHB_BASE) && num == 7)
			return false;
		else if (((uint32_t)GPIOx == GPIOF_BASE || (uint32_t)GPIOx == GPIOF_AHB_BASE) && num == 0)	
			return false;
	}
	
	GPIOx->DIR |= dir << num;
	GPIOx->AMSEL &= ~(1 << num);
	
	if(mode == GPIO_ALTERNATE)
	{
		GPIOx->AFSEL |= 1 << num;
		return true;
	}
	else
		GPIOx->AFSEL &= ~(1 << num);
	
	GPIOx->DEN |= 1 << num;
	
	switch(dir)
	{
		case GPIO_DIR_INPUT:
			switch(mode)
			{
				case GPIO_IN_PULL_DOWN:
					GPIOx->PDR |= 1 << num;
					break;
				case GPIO_IN_PULL_UP:
					GPIOx->PUR |= 1 << num;
					break;
				default:
					return false;
			}
			break;
			
		case GPIO_DIR_OUTPUT:
			switch(mode)
			{
				case GPIO_OUT_OPEN_DRAIN:
					GPIOx->ODR |= 1 << num;
					break;
				case GPIO_OUT_STRENGTH_2MA:
					GPIOx->DR2R |= 1 << num;
					break;
				case GPIO_OUT_STRENGTH_4MA:
					GPIOx->DR4R |= 1 << num;
					break;
				case GPIO_OUT_STRENGTH_8MA:
					GPIOx->DR8R |= 1 << num;
					break;
				case GPIO_OUT_SLEWRATE:
					if(GPIOA->DR8R & 1 << num)
						GPIOx->SLR |= 1 << num;
					else
						return false;
					break;
				default:
						return false;				
			}
			break;
		default:
			return false;			
	}
	return true;
}
