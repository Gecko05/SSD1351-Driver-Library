#include "build/temp/_test_ssd1351.c"
#include "ssd1351.h"
#include "mock_stm32l1xx_hal.h"
#include "unity.h"
uint16_t x;











extern DRAM displayRAM;

uint16_t compRAM[16384];

int16_t x_pos;

int16_t y_pos;

uint16_t color;

uint16_t a_pos;



void printDRAM(void){

 for (int i = 0; i < 16384; i++){

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

 HAL_SPI_Transmit_CMockIgnore();

 HAL_GPIO_WritePin_CMockIgnore();

 HAL_Delay_CMockIgnore();

 memset(displayRAM.halfw, 0, 16384);

}



void tearDown(void){



}



void test_write_pixel_SSD1351(void){



 update_pixel_params(120, 0, 0xFFAA);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((displayRAM.halfw[a_pos])), (UNITY_INT)(UNITY_UINT16)((color)), (

((void *)0)

), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_UINT16);



 update_pixel_params(0, 0, 0xC0AB);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((displayRAM.halfw[a_pos])), (UNITY_INT)(UNITY_UINT16)((color)), (

((void *)0)

), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_UINT16);



 update_pixel_params(127, 127, 0x185A);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((displayRAM.halfw[a_pos])), (UNITY_INT)(UNITY_UINT16)((color)), (

((void *)0)

), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_UINT16);



 update_pixel_params(0, 99, 0xAFE1);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((displayRAM.halfw[a_pos])), (UNITY_INT)(UNITY_UINT16)((color)), (

((void *)0)

), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_UINT16);







 memcpy(compRAM, displayRAM.halfw, 16384);



 update_pixel_params(7148, 99, 0xA458);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM.halfw)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);



 update_pixel_params(0, 129, 0xA458);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM.halfw)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(69), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);



 update_pixel_params(-16, -1, 0xA458);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM.halfw)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);



 update_pixel_params(-16, 0, 0xA458);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM.halfw)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(77), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);



 update_pixel_params(0, -11512, 0xA458);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM.halfw)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(81), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);

}
