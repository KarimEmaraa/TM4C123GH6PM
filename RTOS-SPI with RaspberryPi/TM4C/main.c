#define TARGET_IS_BLIZZARD_RB1
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/ssi.h"
#include "FreeRTOS.h"
#include "task.h"
#include "portable.h"
#include "semphr.h"
#include "queue.h"

#define QUEUE_SIZE 8UL

xQueueHandle mQueue;

void recTask(void *);
void ssi_handle(void)
{
    MAP_SSIIntClear(SSI0_BASE, SSI_RXFF);
    portBASE_TYPE xHigherPrioTask = pdFALSE, xStatus;
    uint_fast32_t i = 0;
    //if receive FIFO is not empty
    if(MAP_SSIIntStatus(SSI0_BASE, false) & 0x4)
    {
        //if receive FIFO is not empty
        while(MAP_SSIIntStatus(SSI0_BASE, false) & 0x4)
        {
            MAP_SSIDataGetNonBlocking(SSI0_BASE, &i);
            xStatus = xQueueSendToBackFromISR(mQueue,(void *)&i, &xHigherPrioTask);
            if(xStatus != pdTRUE)
                break;
        }
    }
    portYIELD_FROM_ISR(xHigherPrioTask);
}


int main(void)
{
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_CLKOUT_MOSC | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	/*SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);*/

    MAP_GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
    MAP_GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    MAP_GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    MAP_GPIOPinConfigure(GPIO_PA4_SSI0RX);
    MAP_GPIOPinConfigure(GPIO_PA5_SSI0TX);

    MAP_SSIClockSourceSet(SSI0_BASE, SSI_CLOCK_SYSTEM);
    MAP_SSIConfigSetExpClk(SSI0_BASE, 80000000, SSI_FRF_MOTO_MODE_0, SSI_MODE_SLAVE, 5000000, 8);
    MAP_SSIEnable(SSI0_BASE);

    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
/*
    GPIOPinTypeSSI(GPIO_PORTB_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_4 | GPIO_PIN_7);
    GPIOPinConfigure(GPIO_PB4_SSI2CLK);
    GPIOPinConfigure(GPIO_PB5_SSI2FSS);
    GPIOPinConfigure(GPIO_PB6_SSI2RX);
    GPIOPinConfigure(GPIO_PB7_SSI2TX);

    SSIClockSourceSet(SSI2_BASE, SSI_CLOCK_SYSTEM);
    SSIConfigSetExpClk(SSI2_BASE, 80000000, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 5000000, 8);
    SSIEnable(SSI2_BASE);*/

    MAP_SSIIntEnable(SSI0_BASE, SSI_RXFF);
    MAP_IntEnable(INT_SSI0_TM4C123);
    MAP_IntPrioritySet(INT_SSI0_TM4C123, 0x30);
    MAP_IntMasterEnable();

    mQueue = xQueueCreate(QUEUE_SIZE, sizeof(uint8_t));

    if(mQueue != NULL)
    {
        xTaskCreate(recTask, NULL, 100, NULL, 1, NULL);
        vTaskStartScheduler();
    }


    /*for (int i = 0; i < 7; ++i)
    {
        SSIDataPutNonBlocking(SSI2_BASE, 'a');
        for (int16_t k = 0; k < 1000; ++k) {

        }
    }

    if(rec[0] == 'a')
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
    }*/

    while(1)
    {

    }


}

void recTask(void * param)
{
    BaseType_t xStatus;
    uint8_t item = 0;
    while(1)
    {
        xStatus = xQueueReceive(mQueue, (void*)&item, portMAX_DELAY);
        if(xStatus == pdPASS)
        {
            if(item == 'a')
            {
                MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
            }
            else
                MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
        }
    }
}

void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}
