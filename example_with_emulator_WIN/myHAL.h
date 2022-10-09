#ifndef MY_HAL_H
#define MY_HAL_H

#include "stdint.h"

#define GPIOA 0
#define GPIOB 0
#define GPIOC 0
#define GPIOD 0
#define GPIOE 0

#define GPIO_PIN_0 0
#define GPIO_PIN_1 1
#define GPIO_PIN_2 2
#define GPIO_PIN_3 3
#define GPIO_PIN_4 4
#define GPIO_PIN_5 5

void SPI_TXBuffer(uint8_t *buffer, uint32_t len);

void SPI_TXByte(uint8_t data);

void GPIO_SetPin(uint16_t Port, uint16_t Pin);

void GPIO_ResetPin(uint16_t Port, uint16_t Pin);

void HAL_Delay(uint16_t ms);

void closeEmulatorSocket();

#endif // MY_HAL_H