#include "build/temp/_test_ssd1351.c"
#include "ssd1351.h"
#include "mock_stm32l1xx_hal.h"
#include "unity.h"




extern uint16_t displayRAM[16384];

uint8_t x_pos;

uint8_t y_pos;

uint16_t color;

uint16_t a_pos;



void printDRAM(void){

 for (int i = 0; i < 128*128; i++){

  printf("%i", displayRAM[i]);

 }

}



void setUp(void){

 HAL_SPI_Transmit_CMockIgnore();

 HAL_GPIO_WritePin_CMockIgnore();

 HAL_Delay_CMockIgnore();

 memset(displayRAM, 0, 16384);

}



void tearDown(void){



}



void update_pixel_params(uint8_t x, uint8_t y, uint16_t col){

 x_pos = x;

 y_pos = y;

 color = col;

 a_pos = x_pos + (128 * y_pos);

}



void test_write_pixel_SSD1351(void){



 update_pixel_params(120, 0, 0xFFAA);

 write_pixel_SSD1351(color, x_pos, y_pos);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((displayRAM[a_pos])), (UNITY_INT)(UNITY_UINT16)((color)), (

((void *)0)

), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_UINT16);



 update_pixel_params(0, 0, 0xC0AB);

 write_pixel_SSD1351(color, x_pos, y_pos);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((displayRAM[a_pos])), (UNITY_INT)(UNITY_UINT16)((color)), (

((void *)0)

), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_UINT16);



 update_pixel_params(127, 127, 0x185A);

 write_pixel_SSD1351(color, x_pos, y_pos);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((displayRAM[a_pos])), (UNITY_INT)(UNITY_UINT16)((color)), (

((void *)0)

), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_UINT16);



 update_pixel_params(0, 99, 0xAFE1);

 write_pixel_SSD1351(color, x_pos, y_pos);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((displayRAM[a_pos])), (UNITY_INT)(UNITY_UINT16)((color)), (

((void *)0)

), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_UINT16);





 update_pixel_params(201, 99, 0xA458);

 write_pixel_SSD1351(color, x_pos, y_pos);

 update_pixel_params(0, 99, 0xAFE1);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((displayRAM[a_pos])), (UNITY_INT)(UNITY_UINT16)((color)), (

((void *)0)

), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_UINT16);



 update_pixel_params(0, 255, 0xA458);

 write_pixel_SSD1351(color, x_pos, y_pos);

 update_pixel_params(127, 127, 0x185A);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((displayRAM[a_pos])), (UNITY_INT)(UNITY_UINT16)((color)), (

((void *)0)

), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_UINT16);

}
