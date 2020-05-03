#ifndef STM32L1_H
#define STM32L1_H

/* This header was designed to mock the STM32L1XX HAL Interface */
#include "stdint.h"

typedef int SPI_HandleTypeDef;
SPI_HandleTypeDef hspi2;

typedef enum
{
  GPIO_PIN_RESET = 0,
  GPIO_PIN_SET
}GPIO_PinState;

struct gpio_struct{
  int gpioa[11];
  int gpiob[11];
  int gpioc[11];
  int gpiod[11];
  int gpioe[11];
}test_gpio_data;

#define GPIOA test_gpio_data.gpioa
#define GPIOB test_gpio_data.gpiob
#define GPIOC test_gpio_data.gpioc
#define GPIOD test_gpio_data.gpiod
#define GPIOE test_gpio_data.gpioe

#define GPIO_PIN_0 0
#define GPIO_PIN_1 1
#define GPIO_PIN_2 2
#define GPIO_PIN_3 3
#define GPIO_PIN_4 4
#define GPIO_PIN_5 5
#define GPIO_PIN_6 6
#define GPIO_PIN_7 7
#define GPIO_PIN_8 8
#define GPIO_PIN_9 9
#define GPIO_PIN_10 10

void HAL_Delay(uint32_t delay);

//HAL_SPI_Transmit(HSSD, &(uint8_t){cmd}, 1, SPI_TIMEOUT);
void HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t * data, uint16_t len, uint32_t timeout);

void HAL_GPIO_WritePin(int *gpio_port, int gpio_pin, GPIO_PinState state);

#endif // STM32L1_H
