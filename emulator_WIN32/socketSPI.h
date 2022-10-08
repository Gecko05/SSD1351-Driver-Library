#ifndef SOCKET_SPI_H
#define SOCKET_SPI_H

#include "stdint.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

void socketSPISendData(uint8_t *dataBytes, uint32_t len);

void closeSocketSPI();

#endif