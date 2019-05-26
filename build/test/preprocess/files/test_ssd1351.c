#include "build/temp/_test_ssd1351.c"
#include "ssd1351.h"
#include "mock_stm32l1xx_hal.h"
#include "unity.h"




extern uint16_t displayRAM[];

uint16_t compRAM[16384];

int16_t x_pos;

int16_t y_pos;

uint16_t color;

uint16_t a_pos;



void printDRAM(void){

 for (int i = 0; i < 128*128; i++){

  printf("%i", displayRAM[i]);

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

 memset(displayRAM, 0, 16384);

}



void tearDown(void){



}







void test_write_pixel_SSD1351(void){



 update_pixel_params(120, 0, 0xFFAA);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((displayRAM[a_pos])), (UNITY_INT)(UNITY_UINT16)((color)), (

((void *)0)

), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_UINT16);



 update_pixel_params(0, 0, 0xC0AB);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((displayRAM[a_pos])), (UNITY_INT)(UNITY_UINT16)((color)), (

((void *)0)

), (UNITY_UINT)(47), UNITY_DISPLAY_STYLE_UINT16);



 update_pixel_params(127, 127, 0x185A);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((displayRAM[a_pos])), (UNITY_INT)(UNITY_UINT16)((color)), (

((void *)0)

), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_UINT16);



 update_pixel_params(0, 99, 0xAFE1);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((displayRAM[a_pos])), (UNITY_INT)(UNITY_UINT16)((color)), (

((void *)0)

), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_UINT16);





 memcpy(compRAM, displayRAM, 16384 * 2);



 update_pixel_params(7148, 99, 0xA458);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);



 update_pixel_params(0, 129, 0xA458);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(66), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);



 update_pixel_params(-16, -1, 0xA458);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(70), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);



 update_pixel_params(-16, 0, 0xA458);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);



 update_pixel_params(0, -11512, 0xA458);

 write_pixel_SSD1351(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(78), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);

}
