#include "build/temp/_test_ssd1351.c"
#include "src/ssd1351.h"
#include "build/test/mocks/mock_myHAL.h"
#include "/home/gecko/gems/gems/ceedling-0.29.1/vendor/unity/src/unity.h"




extern DRAM displayRAM;

uint16_t compRAM[16384];

int16_t x_pos;

int16_t y_pos;

int16_t x_0;

int16_t y_0;

int16_t x_1;

int16_t y_1;

int16_t w;

int16_t h;

uint16_t a_0;

uint16_t a_1;

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

 a_pos = (127 - x_pos) + (128 * y_pos);

}



void print_compRAM(void){

 for (int i = 0; i < 16384; i++){

  printf("%x ", compRAM[i]);

 }

 printf("\n");

}



void print_dispRAM(void){

 for (int i = 0; i < 16384; i++){

  printf("%x ", displayRAM.halfw[i]);

 }

 printf("\n");

}



void setUp(void){

 SPI_TXBuffer_CMockIgnore();

 SPI_TXByte_CMockIgnore();

 GPIO_SetPin_CMockIgnore();



 memset(displayRAM.halfw, 0, 16384);

}



void test_SSD1351_write_pixel(void){



 update_pixel_params(120, 0, 0xFFAA);

 SSD1351_write_pixel(x_pos, y_pos, color);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((color)), (UNITY_INT)(UNITY_UINT16)((displayRAM.halfw[a_pos])), (

((void *)0)

), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_UINT16);



 update_pixel_params(0, 0, 0xC0AB);

 SSD1351_write_pixel(x_pos, y_pos, color);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((color)), (UNITY_INT)(UNITY_UINT16)((displayRAM.halfw[a_pos])), (

((void *)0)

), (UNITY_UINT)(64), UNITY_DISPLAY_STYLE_UINT16);



 update_pixel_params(127, 127, 0x185A);

 SSD1351_write_pixel(x_pos, y_pos, color);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((color)), (UNITY_INT)(UNITY_UINT16)((displayRAM.halfw[a_pos])), (

((void *)0)

), (UNITY_UINT)(68), UNITY_DISPLAY_STYLE_UINT16);



 update_pixel_params(0, 99, 0xAFE1);

 SSD1351_write_pixel(x_pos, y_pos, color);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((color)), (UNITY_INT)(UNITY_UINT16)((displayRAM.halfw[a_pos])), (

((void *)0)

), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_UINT16);







 memcpy(compRAM, displayRAM.halfw, 32768);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM.halfw)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(77), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);



 update_pixel_params(7148, 99, 0xA458);

 SSD1351_write_pixel(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM.halfw)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(81), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);



 update_pixel_params(0, 129, 0xA458);

 SSD1351_write_pixel(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM.halfw)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(85), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);



 update_pixel_params(-16, -1, 0xA458);

 SSD1351_write_pixel(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM.halfw)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);



 update_pixel_params(-16, 0, 0xA458);

 SSD1351_write_pixel(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM.halfw)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(93), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);



 update_pixel_params(0, -11512, 0xA458);

 SSD1351_write_pixel(x_pos, y_pos, color);

 UnityAssertEqualIntArray(( const void*)((compRAM)), ( const void*)((displayRAM.halfw)), (UNITY_UINT32)((16384)), (

((void *)0)

), (UNITY_UINT)(97), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);

}
