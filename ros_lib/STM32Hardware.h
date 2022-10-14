#ifndef _STM32_HARDWARE_H_
#define _STM32_HARDWARE_H_

#include "ringbuffer.h"
#include "main.h"
#include "stm32f4xx_hal.h"


extern UART_HandleTypeDef huart2;
extern struct ringbuffer rb;



class STM32Hardware
{
public:
	STM32Hardware() {
	}

	void init() {
	}

	// Read a byte of data from ROS connection.
	// If no data , returns -1
	int read()
	{
		uint32_t r;
		uint8_t ch = -1;

		__HAL_UART_DISABLE_IT(&huart2, UART_IT_RXNE);
		r = ringbuffer_getchar(&rb, &ch);
		__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);

		if (1 == r)
			return ch;
		else
			return -1;
	}

	// Send a byte of data to ROS connection
	void write(uint8_t* data, int length)
	{
		HAL_UART_Transmit(&huart2, data, length, HAL_MAX_DELAY);
	}

	// Returns milliseconds since start of program
	unsigned long time(void)
	{
		return HAL_GetTick();
	}

};

#endif

