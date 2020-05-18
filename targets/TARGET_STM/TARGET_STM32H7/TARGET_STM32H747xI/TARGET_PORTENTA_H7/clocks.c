#include <stdbool.h>
#include "device/stm32h7xx_hal.h"
#include "device/stm32h7xx_hal_uart.h"

extern bool isBetaBoard();

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {

	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    //printf("called HAL_UART_MspInit\n");

	//PeriphClkInitStruct.PLL2.PLL2State = RCC_PLL_ON;
    //PeriphClkInitStruct.PLL2.PLL2Source = RCC_PLLSOURCE_HSE;
    if (isBetaBoard()) {
    	PeriphClkInitStruct.PLL2.PLL2M = 27;
    } else {
    	PeriphClkInitStruct.PLL2.PLL2M = 25;
    }
    PeriphClkInitStruct.PLL2.PLL2N = 200;
    PeriphClkInitStruct.PLL2.PLL2P = 2;
    PeriphClkInitStruct.PLL2.PLL2Q = 2;
    PeriphClkInitStruct.PLL2.PLL2R = 2;

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_USART234578 | RCC_PERIPHCLK_USART16;
	PeriphClkInitStruct.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PLL2;
	PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_PLL2;
  	PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_PLL2;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
};