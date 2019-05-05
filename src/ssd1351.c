#include "ssd1351.h"
#include "cmsis_os.h"

/**
  * @brief  Writes data to the SSD1351 OLED Display
  * @param  cmd: can be true to write a command
  * @param  data: pointer to the data buffer
  * @param  len: integer to specify data length
  * @retval None
  */
void write_SSD1351Command(uint8_t cmd){
  HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
  HAL_SPI_Transmit(HSSD, &(uint8_t){cmd}, 1, SPI_TIMEOUT);
  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);
}

void write_SSD1351Data(uint8_t data, uint32_t len){
  HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
  HAL_SPI_Transmit(HSSD, &(uint8_t){data}, len, SPI_TIMEOUT);
  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);
}

/**
  * @brief  Initializes the SSD1351 OLED Display
  * @retval None
  */
void init_SSD1351(void){
  HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_SET);
  vTaskDelay(2/portTICK_PERIOD_MS);
  HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_RESET);
  vTaskDelay(2/portTICK_PERIOD_MS);
  HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_SET);
  vTaskDelay(2/portTICK_PERIOD_MS);
  write_SSD1351Command(0xAF);
  vTaskDelay(600/portTICK_PERIOD_MS);
}
