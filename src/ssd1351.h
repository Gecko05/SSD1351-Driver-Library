#ifndef SSD1351_H
#define SSD1351_H

#include "stm32l1xx_hal.h"
#include "stdbool.h"

//--------- Configure this
// PC0 = RESET      PC1 = D/C#      PB0 = CS

#define RESET_PORT GPIOC
#define RESET_PIN GPIO_PIN_0
#define DC_PORT GPIOC
#define DC_PIN  GPIO_PIN_1
#define CS_PORT GPIOB
#define CS_PIN GPIO_PIN_0
#define SPI_TIMEOUT 100

extern SPI_HandleTypeDef hspi2;
#define HSSD &hspi2
//------------------------



void init_SSD1351(void);

void write_SSD1351Command(uint8_t data);

void write_SSD1351Data(uint8_t data, uint32_t len);

#endif //SSD1351_H
