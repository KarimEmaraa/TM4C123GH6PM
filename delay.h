/*
 * delay.h
 *
 *  Created on: Apr 18, 2018
 *      Author: karim
 */

#ifndef DELAY_H_
#define DELAY_H_

#define CPU_FREQ         80000000ULL
#define TIMER_BASE       WTIMER0_BASE

#define TARGET_IS_BLIZZARD_RB1
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
#include "inc/hw_timer.h"

/**
 * @brief Provides a cpu delay for specific time.
 * @time  Time required to delay in seconds.
 * @return void.
 */
void delay_s(uint8_t time);

/**
 * @brief Provides a cpu delay for specific time.
 * @time  Time required to delay in milliseconds.
 * @return void.
 */
void delay_ms(uint16_t time);

/*
 * @brief Provides a cpu delay for specific time.
 * @time Time requited to dlay in microseconds.
 * @return void.
 */
void delay_us(uint16_t time);

#endif /* DELAY_H_ */
