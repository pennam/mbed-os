#include <stddef.h>
#include "cyhal_sdio.h"
#include "cyhal_spi.h"
#include "cyhal_gpio.h"
#include <stdio.h>

void Cy_SysLib_Delay(uint32_t milliseconds) {
	thread_sleep_for(milliseconds);
}

void Cy_SysLib_DelayUs(uint16_t microseconds) {
	wait_us(microseconds);
}