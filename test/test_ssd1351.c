#include "unity.h"
#include "mock_stm32l1xx_hal.h"
#include "ssd1351.h"

extern uint16_t displayRAM[];
uint8_t x_pos;
uint8_t y_pos;
uint16_t color;
uint16_t a_pos;

void setUp(void){
	HAL_SPI_Transmit_Ignore();
	HAL_GPIO_WritePin_Ignore();
	HAL_Delay_Ignore();
}

void tearDown(void){

}

void update_params(uint8_t x, uint8_t y, uint16_t col){
	x_pos = x;
	y_pos = y;
	color = col;
	a_pos = x_pos + (128 * y_pos);
}

void test_write_pixel_SSD1351(void){
	update_params(120, 4, 0xFFAA);
	write_pixel_SSD1351(color, x_pos, y_pos);
	TEST_ASSERT_EQUAL_UINT16(displayRAM[a_pos], color);

	update_params(0, 0, 0xC0AB);
	write_pixel_SSD1351(color, x_pos, y_pos);
	TEST_ASSERT_EQUAL_UINT16(displayRAM[a_pos], color);

	update_params(127, 127, 0x185A);
	write_pixel_SSD1351(color, x_pos, y_pos);
	TEST_ASSERT_EQUAL_UINT16(displayRAM[a_pos], color);

	update_params(2, 99, 0xAFE1);
	write_pixel_SSD1351(color, x_pos, y_pos);
	TEST_ASSERT_EQUAL_UINT16(displayRAM[a_pos], color);
}
