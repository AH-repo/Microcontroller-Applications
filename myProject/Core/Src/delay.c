/*
 * delay.c
 *
 *  Created on: Mar 18, 2025
 *      Author: admin
 */
#include <stdint.h>
#include "delay.h"
static volatile uint64_t ticks;
void SysTick_Handler(void){
	ticks++;
}




uint64_t msGetTicks(void) {
	return ticks;
}
void msDelay(uint64_t ms){
	int temp = ticks+ms;
    while (ticks < temp) {
        ;
    }
}
