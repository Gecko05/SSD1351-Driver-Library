#include "unity.h"
#include "mock_stm32l1xx_hal.h"
#include "ssd1351.h"
#include "string.h"

extern DRAM displayRAM;
uint16_t compRAM[DRAM_SIZE_16];
int16_t x_pos;
int16_t y_pos;
uint16_t color;
uint16_t a_pos;

void printDRAM(void){
	for (int i = 0; i < DRAM_SIZE_16; i++){
		printf("%i", displayRAM.halfw[i]);
	}
}

void update_pixel_params(int16_t x, int16_t y, uint16_t col){
	x_pos = x;
	y_pos = y;
	color = col;
	a_pos = x_pos + (128 * y_pos);
}

void setUp(void){
	HAL_SPI_Transmit_Ignore();
	HAL_GPIO_WritePin_Ignore();
	HAL_Delay_Ignore();
	memset(displayRAM.halfw, 0, 16384);
}

void tearDown(void){

}

void test_write_pixel_SSD1351(void){
/* Test with various positions */
	update_pixel_params(120, 0, 0xFFAA);
	write_pixel_SSD1351(x_pos, y_pos, color);
	TEST_ASSERT_EQUAL_UINT16(displayRAM.halfw[a_pos], color);

	update_pixel_params(0, 0, 0xC0AB);
	write_pixel_SSD1351(x_pos, y_pos, color);
	TEST_ASSERT_EQUAL_UINT16(displayRAM.halfw[a_pos], color);

	update_pixel_params(127, 127, 0x185A);
	write_pixel_SSD1351(x_pos, y_pos, color);
	TEST_ASSERT_EQUAL_UINT16(displayRAM.halfw[a_pos], color);

	update_pixel_params(0, 99, 0xAFE1);
	write_pixel_SSD1351(x_pos, y_pos, color);
	TEST_ASSERT_EQUAL_UINT16(displayRAM.halfw[a_pos], color);

/* Test with positions outside of the screen dimensions */

	memcpy(compRAM, displayRAM.halfw, DRAM_SIZE_16);

	update_pixel_params(7148, 99, 0xA458);
	write_pixel_SSD1351(x_pos, y_pos, color);
	TEST_ASSERT_EQUAL_UINT16_ARRAY(compRAM, displayRAM.halfw, DRAM_SIZE_16);

	update_pixel_params(0, 129, 0xA458);
	write_pixel_SSD1351(x_pos, y_pos, color);
	TEST_ASSERT_EQUAL_UINT16_ARRAY(compRAM, displayRAM.halfw, DRAM_SIZE_16);

	update_pixel_params(-16, -1, 0xA458);
	write_pixel_SSD1351(x_pos, y_pos, color);
	TEST_ASSERT_EQUAL_UINT16_ARRAY(compRAM, displayRAM.halfw, DRAM_SIZE_16);

	update_pixel_params(-16, 0, 0xA458);
	write_pixel_SSD1351(x_pos, y_pos, color);
	TEST_ASSERT_EQUAL_UINT16_ARRAY(compRAM, displayRAM.halfw, DRAM_SIZE_16);

	update_pixel_params(0, -11512, 0xA458);
	write_pixel_SSD1351(x_pos, y_pos, color);
	TEST_ASSERT_EQUAL_UINT16_ARRAY(compRAM, displayRAM.halfw, DRAM_SIZE_16);
}
