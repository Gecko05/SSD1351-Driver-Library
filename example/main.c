#include "ssd1351.h"

int main(int argc, char *argv[]) {
    SSD1351_init();
    SSD1351_fill(COLOR_BLACK);
    SSD1351_set_cursor(0, 0);
    SSD1351_printf(COLOR_AQUA, Font_11x18, "Hello world!");
    SSD1351_update();
    SSD1351_DelayMs(1000);
    return 0;
}