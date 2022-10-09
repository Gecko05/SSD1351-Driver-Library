#include "myHAL.h"
#include "socketSPI.h"

#ifdef _WIN64
#include "time.h"

void SPI_TXBuffer(uint8_t *buffer, uint32_t len) {
    socketSPISendData(buffer, len);
}

void SPI_TXByte(uint8_t data) {
    socketSPISendData(&(uint8_t){data}, 1);
}

void GPIO_SetPin(uint16_t Port, uint16_t Pin) {
    // do nothing
}

void GPIO_ResetPin(uint16_t Port, uint16_t Pin) {
    // do nothing
}

void HAL_Delay(uint16_t ms) {
    clock_t start = clock();
    clock_t elapsed = clock() - start;
    while (elapsed < ms) {
        // wait
        elapsed = clock() - start;
    }
}

void closeEmulatorSocket() {
    closeSocketSPI();
}
#endif