#include "ssd1351.h" // Remember to configure this file to your own hardware
#include "math.h"
#include "stdlib.h"

#define DEMO_CIRCLES

int main(){
  SSD1351_init();
  SSD1351_fill(COLOR_BLACK);
  SSD1351_update();
  int r = 50;
  int g = 100;
  int b = 240;
  int gd = 1;
#ifdef DEMO_CIRCLES
  int c0, c1, c2, c3, c4;
  c0 = 5;
  c1 = 25;
  c2 = 45;
  c3 = 65;
  c4 = 85;
#endif // DEMO_CIRCLES
  while(1){
#ifdef DEMO_PRINT
    //          D E M O    P R I N T
    SSD1351_set_cursor(0, 0);
    SSD1351_printf(SSD1351_get_rgb(r, g, b), med_font, "Hello worldI spent \n%i %s\n", 17, "dollars");
    SSD1351_printf(COLOR_RED, small_font, "\nfor this");
    SSD1351_printf(SSD1351_get_rgb(245, 255, 20), big_font, "\nSSD1351");
    if (gd){
      g+=3;
      b-=3;
    }
    else{
      g-=3;
      b+=3;
    }
    if( b <= 100){
      gd = !gd;
    }
    else if (g <= 100){
      gd = !gd;
    }
#endif // DEMO_PRINT
#ifdef DEMO_RECTANGLES
    //          D E M O    R E C T A N G L E S
    for (int i = 128; i > 0;i-=12){
      SSD1351_draw_filled_rect( 64 - i/2, 64 - i/2, i, i, 0x1111 + rand());
    }
#endif // DEMO_RECTANGLES
#ifdef DEMO_CIRCLES
    //          D E M O    C I R C L E S
    c0+=5;
    c1+=5;
    c2+=5;
    c3+=5;
    c4+=5;
    if (c0 > 90){
      c0 = 5;
    }
    if (c1 > 90){
      c1 = 5;
    }
    if (c2 > 90){
      c2 = 5;
    }
    if (c3 > 90){
      c3 = 5;
    }
    if (c4 > 90){
      c4 = 5;
    }
    int arr[5] = {c0, c1, c2, c3, c4};
    int blu[5] = {150, 190, 250, 190, 150};
    int green[5] = {50, 80, 130, 80, 50};
    int maxi, max = 0;
    for (int k = 0; k < 5; k++){
      max = 0;
      for (int j = 0; j < 5; j++){
        if (arr[j] > max){
          max = arr[j];
          maxi = j;
        }
      }
      SSD1351_draw_filled_circle(64, 64, arr[maxi], SSD1351_get_rgb(20, green[maxi], blu[maxi]));
      arr[maxi] = 0;
    }
#endif // DEMO_CIRCLES
  //          D E M O    S P R I T E S
#ifdef DEMO_SPRITES
SSD1351_draw_sprite(0, 0, &sprite0);
#endif // DEMO_SPRITES
    SSD1351_update();
    HAL_Delay(33);
  }
}