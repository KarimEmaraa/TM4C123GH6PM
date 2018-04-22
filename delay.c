/*
 * delay.c
 *
 *  Created on: Apr 18, 2018
 *      Author: karim
 */

#include "delay.h"

void delay_s(uint8_t time)
{
    uint32_t val = ((time * CPU_FREQ / 40000UL) - 1);
    MAP_TimerLoadSet(TIMER_BASE, TIMER_A, val);
    MAP_TimerPrescaleSet(TIMER_BASE, TIMER_A, 40000);
    MAP_TimerEnable(TIMER_BASE, TIMER_A);
    while(!(MAP_TimerIntStatus(TIMER_BASE, false) & (1 << 0)));
    MAP_TimerIntClear(TIMER_BASE, TIMER_TIMA_TIMEOUT);

}

void delay_ms(uint16_t time)
{
    uint32_t val = (time * (CPU_FREQ / (40000 * 1000))) - 1;
    MAP_TimerLoadSet(TIMER_BASE, TIMER_A, val);
    MAP_TimerPrescaleSet(TIMER_BASE, TIMER_A, 40000UL);
    MAP_TimerEnable(TIMER_BASE, TIMER_A);
    while(!(MAP_TimerIntStatus(TIMER_BASE, false) & (1 << 0)));
    MAP_TimerIntClear(TIMER_BASE, TIMER_TIMA_TIMEOUT);
}

void delay_us(uint16_t time)
{
    uint32_t val = (time * (CPU_FREQ / (40UL * 1000000UL))) - 1;
    MAP_TimerLoadSet(TIMER_BASE, TIMER_A, val);
    MAP_TimerPrescaleSet(TIMER_BASE, TIMER_A, 40);
    MAP_TimerEnable(TIMER_BASE, TIMER_A);
    while(!(MAP_TimerIntStatus(TIMER_BASE, false) & (1 << 0)));
    MAP_TimerIntClear(TIMER_BASE, TIMER_TIMA_TIMEOUT);
}

